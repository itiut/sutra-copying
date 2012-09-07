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
