#ifndef _IMG32_H_
#define _IMG32_H_

#include "bitmap.h"

class CImage32
{
protected:
    int m_width, m_height;
    void *m_buffer;

public:
    CImage32(void *dummy);
    CImage32(int width, int height);
    Cimage32();
    virtual ~CImage32();

    virtual void Free();
    virtual void Resize(int width, int height);

    void *PixelAddress(int x, int y);
    const void *PixelAddress(int x, int y) const;

    void *PixelAddressNC(int x, int y) {
        return (BYTE *) m_buffer + (m_width * y + x) * sizeof(DWORD);
    }
    const void *PixelAddressNC(int x, int y) const {
        return (BYTE *) m_buffer + (m_width * y + x) * sizeof(DWORD);
    }

    void PixelSet(int x, int y, DWORD color);
    void PixelSetNC(int x, int y, DWORD color);

    DWORD PixelGet(int x, int y) const;
    DWORD PixelGetNC(int x, int y) const;

    int Width() const { return m_width; }
    int Height() const { return m_height; }
    void *Buffer() { return m_buffer; }
    const void *Buffer() const { return m_buffer; }
};

#endif /* _IMG32_H_ */
