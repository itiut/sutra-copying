#ifndef _IMGDIB_H_
#define _IMGDIB_H_

#include "img32.h"

class CImageDIB : public CImage32
{
protected:
    static const unsigned int kBitmapFileHeaderBytes = 14;
    static const unsigned int kBitmapInfoHeaderBytes = 40;
    static const unsigned int kBitmapHeaderBytes = 54;
    BITMAPFILEHEADER bmfh_;
    BITMAPINFO bmi_;

    void InitBitmapHeader();
    void SetBitmapHeader(const unsigned char *header_buf);
    void GetBitmapHeader(unsigned char *header_buf) const;

    void ReadBitmap(const char *filename);

public:
    CImageDIB();
    CImageDIB(int width, int height);
    CImageDIB(const char *filename);
    ~CImageDIB();

    void Free();
    void Resize(int width, int height);

    void WriteBitmap(const char *filename);

    void PrintBitmapHeader();
};

#endif /* _IMGDIB_H_ */
