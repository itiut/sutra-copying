#include "img32.h"

CImage32::CImage32(void *dummy) {
}

CImage32::CImage32(int width, int height) {
    m_buffer = NULL;
    Resize(width, height);
}

CImage32::CImage32() {
    m_buffer = NULL;
    Resize(8, 8);
}

CImage32::~CImage32() {
    Free();
}

void CImage32::Free() {
    if (m_buffer != NULL) {
        free(m_buffer);
        m_buffer = NULL;
    }
}

void CImage32::Resize(int width, int height) {
    Free();
    m_width = width;
    m_height = height;
    m_buffer = malloc(width * height * sizeof(DWORD));
}

void *CImage32::PixelAddress(int x, int y) {
    if (x < 0 || m_width <= x || y < 0 || m_height <= y) {
        return NULL;
    }
    return PixelAddressNC(x, y);
}

const void *CImage32::PixelAddress(int x, int y) const {
    if (x < 0 || m_width <= x || y < 0 || m_height <= y) {
        return NULL;
    }
    return PixelAddressNC(x, y);
}

void CImage32::PixelSet(int x, int y, int color) {
    DWORD *ptr = (DWORD *) PixelAddress(x, y);
    if (ptr == NULL) {
        return;
    }
    *ptr = color;
}

void CImage32::PixelSetNC(int x, int y, int color) {
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
