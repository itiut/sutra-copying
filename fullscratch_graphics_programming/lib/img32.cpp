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

void CImage32::PixelSetNC(int x, int y, DWORD color) {
    DWORD *ptr = (DWORD *) PixelAddressNC(x, y);
    *ptr = color;
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
