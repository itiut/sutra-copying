#include <cstdlib>
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

    TClipSize dst;
    dst.width = Width();
    dst.height = Height();

    if (ClipFillInfo(&dst, &info) == false) {
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

    TClipSize dst;
    dst.width = Width();
    dst.height = Height();

    if (ClipFillInfo(&dst, &info) == false) {
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
