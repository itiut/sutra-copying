#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "img32.h"
#include "blt.h"

CImage32::CImage32(void *dummy) {
    (void) dummy;
}

CImage32::CImage32(int width, int height) {
    buffer_ = NULL;
    Resize(width, height);
}

CImage32::CImage32() {
    buffer_ = NULL;
    Resize(8, 8);
}

CImage32::~CImage32() {
    Free();
}

void CImage32::Free() {
    if (buffer_ != NULL) {
        free(buffer_);
        buffer_ = NULL;
    }
}

void CImage32::Resize(int width, int height) {
    Free();
    width_ = width;
    height_ = height;
    buffer_ = malloc(sizeof(DWORD) * width * height);
}

void *CImage32::PixelAddress(int x, int y) {
    if (x < 0 || width_ <= x || y < 0 || height_ <= y) {
        return NULL;
    }
    return PixelAddressNC(x, y);
}

const void *CImage32::PixelAddress(int x, int y) const {
    if (x < 0 || width_ <= x || y < 0 || height_ <= y) {
        return NULL;
    }
    return PixelAddressNC(x, y);
}

void CImage32::PixelSet(int x, int y, DWORD color) {
    DWORD *ptr = (DWORD *) PixelAddress(x, y);
    if (ptr == NULL) {
        return;
    }
    *ptr = color;
}

void CImage32::PixelSet(int x, int y, DWORD color, BYTE alpha) {
    DWORD *ptr = (DWORD *) PixelAddress(x, y);
    if (ptr == NULL) {
        return;
    }
    ::PixelSet(ptr, &color, alpha);
}

void CImage32::PixelSetNC(int x, int y, DWORD color) {
    DWORD *ptr = (DWORD *) PixelAddressNC(x, y);
    *ptr = color;
}

void CImage32::PixelSetAA(double fx, double fy, DWORD color) {
    int alpha_x = 255.0 * (fx - (int) fx);
    int alpha_y = 255.0 * (fy - (int) fy);

    int alpha[] = {
        (255 - alpha_x) * (255 - alpha_y) / 255,
        alpha_x * (255 - alpha_y) / 255,
        (255 - alpha_x) * alpha_y / 255,
        alpha_x * alpha_y / 255,
    };

    PixelSet(fx, fy, color, alpha[0]);
    PixelSet(fx + 1, fy, color, alpha[1]);
    PixelSet(fx, fy + 1, color, alpha[2]);
    PixelSet(fx + 1, fy + 1, color, alpha[3]);
}

DWORD CImage32::PixelGet(int x, int y) const {
    DWORD *ptr = (DWORD *) PixelAddress(x, y);
    if (ptr == NULL) {
        return 0;
    }
    return *ptr;
}

DWORD CImage32::PixelGetNC(int x, int y) const {
    DWORD *ptr = (DWORD *) PixelAddressNC(x, y);
    return *ptr;
}

DWORD CImage32::PixelGetAA(double fx, double fy) const {
    int alpha_x = 255.0 * (fx - (int) fx);
    int alpha_y = 255.0 * (fy - (int) fy);

    int alpha[] = {
        (255 - alpha_x) * (255 - alpha_y) / 255,
        alpha_x * (255 - alpha_y) / 255,
        (255 - alpha_x) * alpha_y / 255,
        alpha_x * alpha_y / 255,
    };

    int r, g, b;
    r = g = b = 0;

    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            int sx = fx + x;
            int sy = fy + y;

            if (sx < 0) {
                sx = width_ - (-sx) % width_ - 1;
            } else {
                sx = sx % width_;
            }
            if (sy < 0) {
                sy = height_ - (-sy) % height_ - 1;
            } else {
                sy = sy % height_;
            }

            TARGB c;
            c.ARGB = PixelGetNC(sx, sy);
            AddARGB(&r, &g, &b, &c, alpha[y*2 + x]);
        }
    }

    TARGB c;
    c.R = r / 255;
    c.G = g / 255;
    c.B = b / 255;
    return c.ARGB;
}

bool CImage32::PixelFill(int x, int y, int w, int h, DWORD color, BYTE alpha) {
    TClipFillInfo info;
    info.dx = x; info.dy = y;
    info.dw = w; info.dh = h;

    TClipSize dst_block;
    dst_block.width = width_;
    dst_block.height = height_;

    if (ClipFillInfo(&dst_block, &info) == false) {
        return false;
    }

    for (int i = info.dy, end = info.dy + info.dh; i < end; i++) {
        DWORD *dst_addr = (DWORD *) PixelAddress(info.dx, i);
        FillNormal(dst_addr, info.dw, color, alpha);
    }

    return true;
}

bool CImage32::PixelFill(DWORD color, BYTE alpha) {
    return PixelFill(0, 0, width_, height_, color, alpha);
}

bool CImage32::Filter(int x, int y, int w, int h, TFilterType filter, DWORD value) {
    TClipFillInfo info;
    info.dx = x; info.dy = y;
    info.dw = w; info.dh = h;

    TClipSize dst_block;
    dst_block.width = width_;
    dst_block.height = height_;

    if (ClipFillInfo(&dst_block, &info) == false) {
        return false;
    }

    for (int i = info.dy, end = info.dy + info.dh; i < end; i++) {
        DWORD *dst_addr = (DWORD *) PixelAddress(info.dx, i);
        switch (filter) {
        case FLT_AND:
            for (int j = 0; j < info.dw; j++, dst_addr++) {
                *dst_addr &= value;
            }
            break;
        case FLT_OR:
            for (int j = 0; j < info.dw; j++, dst_addr++) {
                *dst_addr |= value;
            }
            break;
        case FLT_XOR:
            for (int j = 0; j < info.dw; j++, dst_addr++) {
                *dst_addr ^= value;
            }
            break;
        case FLT_NOT:
            for (int j = 0; j < info.dw; j++, dst_addr++) {
                *dst_addr = ~*dst_addr;
            }
            break;
        }
    }

    return true;
}

bool CImage32::Filter(TFilterType filter, DWORD value) {
    return Filter(0, 0, Width(), Height(), filter, value);
}

bool CImage32::Blt(const CBltInfo *bi, int dx, int dy, const CImage32 *src, int sx, int sy, int sw, int sh) {
    TClipBltInfo info;
    info.sx = sx; info.sy = sy;
    info.sw = sw; info.sh = sh;
    info.dx = dx; info.dy = dy;

    TClipSize dst_block, src_block;
    dst_block.width  = width_;
    dst_block.height = height_;
    src_block.width  = src->Width();
    src_block.height = src->Height();

    if (ClipBltInfo(&dst_block, &src_block, &info) == false) {
        return false;
    }

    for (int i = info.dy, end = info.dy + info.sh; i < end; i++) {
        DWORD *src_addr = (DWORD *) src->PixelAddress(info.sx, info.sy + i - info.dy);
        DWORD *dst_addr = (DWORD *) PixelAddress(info.dx, i);

        switch (bi->type) {
        case BLT_COPY:
            BltCopy(dst_addr, src_addr, info.sw);
            break;
        case BLT_NORMAL:
            BltNormal(dst_addr, src_addr, info.sw, bi->alpha);
            break;
        case BLT_ALPHA:
            BltNormalAlpha(dst_addr, src_addr, info.sw, bi->alpha);
            break;
        case BLT_KEY:
            BltKey(dst_addr, src_addr, info.sw, bi->alpha, bi->colorkey);
            break;
        case BLT_ADD:
            BltAdd(dst_addr, src_addr, info.sw, bi->alpha);
            break;
        case BLT_MUL:
            BltMul(dst_addr, src_addr, info.sw, bi->alpha);
            break;
        }
    }

    return true;
}

bool CImage32::Blt(const CBltInfo *bi, int dx, int dy, const CImage32 *src) {
    return Blt(bi, dx, dy, src, 0, 0, src->Width(), src->Height());
}

bool CImage32::Blt(int dx, int dy, const CImage32 *src) {
    CBltInfo bi;
    return Blt(&bi, dx, dy, src);
}

bool CImage32::BltAA(double fx, double fy, const CImage32 *src) {
    int alpha_x = 255.0 * (fx - (int) fx);
    int alpha_y = 255.0 * (fy - (int) fy);

    int alpha[] = {
        alpha_x * alpha_y / 255,
        (255 - alpha_x) * alpha_y / 255,
        alpha_x * (255 - alpha_y) / 255,
        (255 - alpha_x) * (255 - alpha_y) / 255,
    };

    int sw = src->Height();
    int sh = src->Width();

    for (int y = fy, y_last = y + sh, sy = 0; y <= y_last; y++, sy++) {
        for (int x = fx, x_last = x + sw, sx = 0; x < x_last; x++, sx++) {
            TARGB c[4];
            c[0].ARGB = src->PixelGet(sx - 1, sy - 1);
            c[1].ARGB = src->PixelGet(sx, sy - 1);
            c[2].ARGB = src->PixelGet(sx - 1, sy);
            c[3].ARGB = src->PixelGet(sx, sy);

            bool p[4];
            std::fill_n(p, 4, true);
            if (sx == 0) {
                p[0] = p[2] = false;
            } else if (sx == sw) {
                p[1] = p[3] = false;
            }
            if (sy == 0 ) {
                p[0] = p[1] = false;
            } else if (sy == sh) {
                p[2] = p[3] = false;
            }

            int a, r, g, b;
            a = r = g = b = 0;

            if (p[0]) {
                AddARGB(&r, &g, &b, &c[0], alpha[0]);
                a += alpha[0];
            }
            if (p[1]) {
                AddARGB(&r, &g, &b, &c[1], alpha[1]);
                a += alpha[1];
            }
            if (p[2]) {
                AddARGB(&r, &g, &b, &c[2], alpha[2]);
                a += alpha[2];
            }
            if (p[3]) {
                AddARGB(&r, &g, &b, &c[3], alpha[3]);
                a += alpha[3];
            }

            if (a != 0) {
                TARGB color;
                color.R = r / a;
                color.G = g / a;
                color.B = b / a;
                PixelSet(x, y, color.ARGB, a);
            }
        }
    }

    return true;
}

bool CImage32::DrawXLine(int x0, int x1, int y, DWORD color, BYTE alpha) {
    if (y < 0 || height_ <= y) {
        return false;
    }
    if (x1 < x0) {
        std::swap(x0, x1);
    }
    if (x1 < 0 || width_ <= x0) {
        return false;
    }

    x0 = std::max(x0, 0);
    x1 = std::min(x1, width_ - 1);

    DWORD *addr = (DWORD *) PixelAddress(x0, y);

    for (int x = x0; x <= x1; x++, addr++) {
        ::PixelSet(addr, &color, alpha);
    }

    return true;
}

bool CImage32::DrawXLineAA(double x0, double x1, int y, DWORD color, BYTE alpha) {
    if (y < 0 || height_ <= y) {
        return false;
    }
    if (x1 < x0) {
        std::swap(x0, x1);
    }
    if (x1 < 0 || width_ <= x0) {
        return false;
    }

    x0 = std::max(x0, 0.0);
    x1 = std::min(x1, width_ - 1.0);

    int ix0 = x0;
    int ix1 = x1;

    if (ix0 == ix1) {
        int aa = 255.0 * (x1 - x0);
        PixelSet(ix0, y, color, aa * alpha / 255);
        return true;
    }

    DWORD *addr = (DWORD *) PixelAddress(ix0, y);

    for (int x = ix0; x <= ix1; x++, addr++) {
        int alpha2 = alpha;

        if (x == ix0) {
            int aa = 255 - (int) (255.0 * (x0 - ix0));
            alpha2 = aa * alpha / 255;
        } else if (x == ix1) {
            int aa = 255.0 * (x1 - ix1);
            alpha2 = aa * alpha / 255;
        }

        ::PixelSet(addr, &color, alpha2);
    }

    return true;
}

bool CImage32::DrawLine(int x0, int y0, int x1, int y1, DWORD color) {
    if (x0 < 0 && x1 < 0) return false;
    if (y0 < 0 && y1 < 0) return false;
    if (x0 > width_ && x1 > width_) return false;
    if (y0 > height_ && y1 > height_) return false;

    if (std::abs(x0 - x1) > std::abs(y0 - y1)) {
        double fy = y0;
        double dy = 0.0;
        if (x0 != x1) {
            dy = (double) (y1 - y0) / (x1 - x0);
        }

        int dx = 1;
        if (x1 < x0) {
            dx = -1;
            dy = -dy;
        }

        for (int x = x0; x != x1; x += dx, fy += dy) {
            PixelSet(x, fy, color);
        }
    } else {
        double fx = x0;
        double dx = 0.0;
        if (y0 != y1) {
            dx = (double) (x1 - x0) / (y1 - y0);
        }

        int dy = 1;
        if (y1 < y0) {
            dy = -1;
            dx = -dx;
        }

        for (int y = y0; y != y1; y += dy, fx += dx) {
            PixelSet(fx, y, color);
        }
    }

    return true;
}

bool CImage32::DrawLineAA(int x0, int y0, int x1, int y1, DWORD color) {
    if (x0 < 0 && x1 < 0) return false;
    if (y0 < 0 && y1 < 0) return false;
    if (x0 > width_ && x1 > width_) return false;
    if (y0 > height_ && y1 > height_) return false;

    if (std::abs(x0 - x1) > std::abs(y0 - y1)) {
        double fy = y0;
        double dy = 0.0;
        if (x0 != x1) {
            dy = (double) (y1 - y0) / (x1 - x0);
        }

        int dx = 1;
        if (x1 < x0) {
            dx = -1;
            dy = -dy;
        }

        for (int x = x0; x != x1; x += dx, fy += dy) {
            int a1 = 255.0 * (fy - (int) fy);
            int a0 = 255 - a1;
            PixelSet(x, fy, color, a0);
            PixelSet(x, fy + 1, color, a1);
        }
    } else {
        double fx = x0;
        double dx = 0.0;
        if (y0 != y1) {
            dx = (double) (x1 - x0) / (y1 - y0);
        }

        int dy = 1;
        if (y1 < y0) {
            dy = -1;
            dx = -dx;
        }

        for (int y = y0; y != y1; y += dy, fx += dx) {
            int a1 = 255.0 * (fx - (int) fx);
            int a0 = 255 - a1;
            PixelSet(fx, y, color, a0);
            PixelSet(fx + 1, y, color, a1);
        }
    }

    return true;
}
