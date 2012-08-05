#ifndef _IMG32_H_
#define _IMG32_H_

#include "bitmap.h"

class CImage32
{
protected:
    int width_, height_;
    void *buffer_;

public:
    CImage32(void *dummy);
    CImage32(int width, int height);
    CImage32();
    virtual ~CImage32();

    virtual void Free();
    virtual void Resize(int width, int height);

    void *PixelAddress(int x, int y);
    const void *PixelAddress(int x, int y) const;

    void *PixelAddressNC(int x, int y) {
        return (BYTE *) buffer_ + (width_ * y + x) * sizeof(DWORD);
    }
    const void *PixelAddressNC(int x, int y) const {
        return (BYTE *) buffer_ + (width_ * y + x) * sizeof(DWORD);
    }

    void PixelSet(int x, int y, DWORD color);
    void PixelSetNC(int x, int y, DWORD color);

    DWORD PixelGet(int x, int y) const;
    DWORD PixelGetNC(int x, int y) const;

    int Width() const { return width_; }
    int Height() const { return height_; }
    void *Buffer() { return buffer_; }
    const void *Buffer() const { return buffer_; }
};

#endif /* _IMG32_H_ */