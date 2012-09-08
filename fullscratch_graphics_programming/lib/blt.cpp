#include <algorithm>
#include "bitmap.h"
#include "blt.h"

bool ClipBltInfo(TClipSize *src, TClipSize *dst, TClipBltInfo *info) {
    if (info->sw + info->dx <= 0) return false;
    if (info->sh + info->dy <= 0) return false;
    if (info->dx >= dst->width)  return false;
    if (info->dy >= dst->height) return false;

    if (info->sx >= src->width)  return false;
    if (info->sy >= src->height) return false;
    if (info->sx + info->sw < 0) return false;
    if (info->sy + info->sh < 0) return false;

    info->sw = std::min(info->sw, src->width - info->sx);
    info->sh = std::min(info->sh, src->height - info->sy);

    if (info->sx < 0) {
        info->dx += std::abs(info->sx);
        info->sw -= std::abs(info->sx);
        info->sx = 0;
    }
    if (info->sy < 0) {
        info->dy += std::abs(info->sy);
        info->sw -= std::abs(info->sy);
        info->sy = 0;
    }

    if (info->dx < 0) {
        info->sx += std::abs(info->dx);
        info->sw -= std::abs(info->dx);
        info->dx = 0;
    }
    if (info->dy < 0) {
        info->sy += std::abs(info->dy);
        info->sh -= std::abs(info->dy);
        info->dy = 0;
    }

    info->sw = std::min(info->sw, dst->width - info->dx);
    info->sh = std::min(info->sh, dst->height - info->dy);

    if (info->sw < 1 || info->sh < 1) return false;

    return true;
}

bool ClipFillInfo(TClipSize *dst, TClipFillInfo *info) {
    if (info->dx >= dst->width)  return false;
    if (info->dy >= dst->height) return false;
    if (info->dx + info->dw <= 0) return false;
    if (info->dy + info->dh <= 0) return false;

    if (info->dx < 0) {
        info->dw -= std::abs(info->dx);
        info->dx = 0;
    }
    if (info->dy < 0) {
        info->dh -= std::abs(info->dy);
        info->dy = 0;
    }

    info->dw = std::min(info->dw, dst->width - info->dx);
    info->dh = std::min(info->dh, dst->height - info->dy);

    return true;
}

void PixelSet(DWORD *dst_addr, DWORD *src_addr, BYTE src_alpha) {
    TARGB src_pixel, dst_pixel;
    src_pixel.ARGB = *src_addr;
    dst_pixel.ARGB = *dst_addr;

    dst_pixel.R += (int) (src_pixel.R - dst_pixel.R) * src_alpha / 255;
    dst_pixel.G += (int) (src_pixel.G - dst_pixel.G) * src_alpha / 255;
    dst_pixel.B += (int) (src_pixel.B - dst_pixel.B) * src_alpha / 255;

    *dst_addr = dst_pixel.ARGB;
}

void PixelSetAdd(DWORD *dst_addr, DWORD *src_addr, BYTE src_alpha) {
    TARGB src_pixel, dst_pixel;
    src_pixel.ARGB = *src_addr;
    dst_pixel.ARGB = *dst_addr;

    int r = dst_pixel.R + (int) src_pixel.R * src_alpha / 255;
    dst_pixel.R = std::min(r, 255);

    int g = dst_pixel.G + (int) src_pixel.G * src_alpha / 255;
    dst_pixel.G = std::min(g, 255);

    int b = dst_pixel.B + (int) src_pixel.B * src_alpha / 255;
    dst_pixel.B = std::min(b, 255);

    *dst_addr = dst_pixel.ARGB;
}


void FillNormal(DWORD *dst_addr, int width, DWORD color, BYTE alpha) {
    for (int i = 0; i < width; i++, dst_addr++) {
        PixelSet(dst_addr, &color, alpha);
    }
}

void BltNormal(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha) {
    for (int i = 0; i < width; i++, dst_addr++, src_addr++) {
        PixelSet(dst_addr, src_addr, alpha);
    }
}

void BltNormalAlpha(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha) {
    for (int i = 0; i < width; i++, dst_addr++, src_addr++) {
        int alpha2 = (int) *((BYTE *) src_addr + 3) * alpha / 255;
        PixelSet(dst_addr, src_addr, alpha2);
    }
}

void BltKey(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha, DWORD colorkey) {
    for (int i = 0; i < width; i++, dst_addr++, src_addr++) {
        if (*src_addr != colorkey) {
            *dst_addr = *src_addr;
        }
    }
}

void BltAdd(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha) {
}
