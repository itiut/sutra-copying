#ifndef _IMG32_H_
#define _IMG32_H_

#include "bitmap.h"
#include "blt.h"

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
    void PixelSet(int x, int y, DWORD color, BYTE alpha);
    void PixelSetNC(int x, int y, DWORD color);

    DWORD PixelGet(int x, int y) const;
    DWORD PixelGetNC(int x, int y) const;

    int Width() const { return width_; }
    int Height() const { return height_; }
    void *Buffer() { return buffer_; }
    const void *Buffer() const { return buffer_; }

    bool PixelFill(int x, int y, int w, int h, DWORD color, BYTE alpha);
    bool PixelFill(DWORD color, BYTE alpha);
    bool Filter(int x, int y, int w, int h, TFilterType filter, DWORD value);
    bool Filter(TFilterType filter, DWORD value);

    bool Blt(const CBltInfo *bi, int dx, int dy, const CImage32 *src, int sx, int sy, int sw, int sh);
    bool Blt(const CBltInfo *bi, int dx, int dy, const CImage32 *src);
    bool Blt(int dx, int dy, const CImage32 *src);

    bool DrawXLine(int x0, int x1, int y, DWORD color, BYTE alpha);
    bool DrawLine(int x0, int y0, int x1, int y1, DWORD color);
};

#endif /* _IMG32_H_ */
