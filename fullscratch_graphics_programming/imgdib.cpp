#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "imgdib.h"

CImageDIB::CImageDIB(int width, int height) : CImage32(NULL) {
    buffer_ = NULL;
    InitBitmapHeader();
    Resize(width, height);
}

CImageDIB::CImageDIB() : CImage32(NULL) {
    buffer_ = NULL;
    InitBitmapHeader();
    Resize(8, 8);
}

CImageDIB::CImageDIB(const char *filename) : CImage32(NULL) {
    buffer_ = NULL;
    ReadBitmap(filename);
}

CImageDIB::~CImageDIB() {
    Free();
}

void CImageDIB::Free() {
    if (buffer_ != NULL) {
        free(buffer_);
        buffer_ = NULL;
    }
}

void CImageDIB::Resize(int width, int height) {
    Free();
    buffer_ = calloc(width * height, sizeof(DWORD));
    if (buffer_ == NULL) {
        perror("CImageDIB::Resize->calloc() failed");
        exit(EXIT_FAILURE);
    }

    width_ = width;
    height_ = height;
}

void CImageDIB::ReadBitmap(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("CImageDIB::ReadBitmap()->fopen() failed");
        exit(EXIT_FAILURE);
    }

    unsigned char header_buf[kBitmapHeaderBytes];
    if (fread(header_buf, sizeof(unsigned char), kBitmapHeaderBytes, fp) != kBitmapHeaderBytes) {
        perror("CImageDIB::ReadBitmap()->fread() failed");
        exit(EXIT_FAILURE);
    }

    SetBitmapHeader(header_buf);

    if (bmfh_.bfType != (WORD) ('B' | 'M' << 8)) {
        fprintf(stderr, "Error: %s is not a bitmap file.\n", filename);
        exit(EXIT_FAILURE);
    }

    if (bmi_.bmiHeader.biBitCount != 24) {
        fprintf(stderr, "Error: this program is only for 24-bits bitmap files.\n");
        fprintf(stderr, "%s is %d-bit(s) bitmap file.\n", filename, header_buf[28]);
        exit(EXIT_FAILURE);
    }


    width_ = bmi_.bmiHeader.biWidth;
    height_ = bmi_.bmiHeader.biHeight;

    buffer_ = calloc(width_ * height_, sizeof(DWORD));
    unsigned long long line_bytes = width_ * 3 + width_ % 4;
    unsigned char *line_buf = (unsigned char *) malloc(line_bytes * sizeof(unsigned char));

    if (buffer_ == NULL || line_buf == NULL) {
        perror("CImageDIB::ReadBitmap()->malloc() failed");
        exit(EXIT_FAILURE);
    }

    for (int y = height_ - 1; y >= 0; y--) {
        if (fread(line_buf, sizeof(unsigned char), line_bytes, fp) != line_bytes) {
            perror("CImageDIB::ReadBitmap()->fread() failed");
            exit(EXIT_FAILURE);
        }
        for (int x = 0; x < width_; x++) {
            memcpy((DWORD *) buffer_ + y * width_ + x, line_buf + x * 3, 3);
        }
    }

    free(line_buf);
    fclose(fp);
}

void CImageDIB::WriteBitmap(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("CImageDIB::WriteBitmap()->fopen() failed");
        exit(EXIT_FAILURE);
    }

    unsigned long long line_bytes = width_ * 3 + width_ % 4;
    bmfh_.bfSize = kBitmapHeaderBytes + height_ * line_bytes;
    bmi_.bmiHeader.biWidth = width_;
    bmi_.bmiHeader.biHeight = height_;

    unsigned char header_buf[kBitmapHeaderBytes];
    GetBitmapHeader(header_buf);

    if (fwrite(header_buf, sizeof(unsigned char), kBitmapHeaderBytes, fp) != kBitmapHeaderBytes) {
        perror("CImageDIB::WriteBitmap()->fwrite() failed");
        exit(EXIT_FAILURE);
    }

    unsigned char *line_buf = (unsigned char *) calloc(line_bytes, sizeof(unsigned char));
    if (line_buf == NULL) {
        perror("CimageDIB::WriteBitmap()->calloc() failed");
        exit(EXIT_FAILURE);
    }

    for (int y = height_ - 1; y >= 0; y--) {
        for (int x = 0; x < width_; x++) {
            memcpy(line_buf + x * 3, (DWORD *) buffer_ + y * width_ + x, 3);
        }
        if (fwrite(line_buf, sizeof(unsigned char), line_bytes, fp) != line_bytes) {
            perror("CImageDIB::WriteBitmap()->fwrite() failed");
            exit(EXIT_FAILURE);
        }
    }

    free(line_buf);
    fclose(fp);
}

void CImageDIB::InitBitmapHeader() {
    bmfh_.bfType = (WORD) ('B' | ('M' << 8));
//    bmfh_.bfSize = 0;
    bmfh_.bfReserved1 = 0;
    bmfh_.bfReserved2 = 0;
    bmfh_.bfOffBits = kBitmapHeaderBytes;
    bmi_.bmiHeader.biSize = kBitmapInfoHeaderBytes;
//    bmi_.bmiHeader.biWidth = 0;
//    bmi_.bmiHeader.biHeight = 0;
    bmi_.bmiHeader.biPlanes = 1;
    bmi_.bmiHeader.biBitCount = 24;
    bmi_.bmiHeader.biCompression = 0;
    bmi_.bmiHeader.biSizeImage = 0;
    bmi_.bmiHeader.biXPelsPerMeter = 0;
    bmi_.bmiHeader.biYPelsPerMeter = 0;
    bmi_.bmiHeader.biClrUsed = 0;
    bmi_.bmiHeader.biClrImportant = 0;
}

void CImageDIB::SetBitmapHeader(const unsigned char *header_buf) {
    memcpy(&bmfh_.bfType,                   header_buf + 0x00, 2);
    memcpy(&bmfh_.bfSize,                   header_buf + 0x02, 4);
    memcpy(&bmfh_.bfReserved1,              header_buf + 0x06, 2);
    memcpy(&bmfh_.bfReserved2,              header_buf + 0x08, 2);
    memcpy(&bmfh_.bfOffBits,                header_buf + 0x0a, 4);
    memcpy(&bmi_.bmiHeader.biSize,          header_buf + 0x0e, 4);
    memcpy(&bmi_.bmiHeader.biWidth,         header_buf + 0x12, 4);
    memcpy(&bmi_.bmiHeader.biHeight,        header_buf + 0x16, 4);
    memcpy(&bmi_.bmiHeader.biPlanes,        header_buf + 0x1a, 2);
    memcpy(&bmi_.bmiHeader.biBitCount,      header_buf + 0x1c, 2);
    memcpy(&bmi_.bmiHeader.biCompression,   header_buf + 0x1e, 4);
    memcpy(&bmi_.bmiHeader.biSizeImage,     header_buf + 0x22, 4);
    memcpy(&bmi_.bmiHeader.biXPelsPerMeter, header_buf + 0x26, 4);
    memcpy(&bmi_.bmiHeader.biYPelsPerMeter, header_buf + 0x2a, 4);
    memcpy(&bmi_.bmiHeader.biClrUsed,       header_buf + 0x2e, 4);
    memcpy(&bmi_.bmiHeader.biClrImportant,  header_buf + 0x32, 4);
}

void CImageDIB::GetBitmapHeader(unsigned char *header_buf) const {
    memcpy(header_buf + 0x00, &bmfh_.bfType,                   2);
    memcpy(header_buf + 0x02, &bmfh_.bfSize,                   4);
    memcpy(header_buf + 0x06, &bmfh_.bfReserved1,              2);
    memcpy(header_buf + 0x08, &bmfh_.bfReserved2,              2);
    memcpy(header_buf + 0x0a, &bmfh_.bfOffBits,                4);
    memcpy(header_buf + 0x0e, &bmi_.bmiHeader.biSize,          4);
    memcpy(header_buf + 0x12, &bmi_.bmiHeader.biWidth,         4);
    memcpy(header_buf + 0x16, &bmi_.bmiHeader.biHeight,        4);
    memcpy(header_buf + 0x1a, &bmi_.bmiHeader.biPlanes,        2);
    memcpy(header_buf + 0x1c, &bmi_.bmiHeader.biBitCount,      2);
    memcpy(header_buf + 0x1e, &bmi_.bmiHeader.biCompression,   4);
    memcpy(header_buf + 0x22, &bmi_.bmiHeader.biSizeImage,     4);
    memcpy(header_buf + 0x26, &bmi_.bmiHeader.biXPelsPerMeter, 4);
    memcpy(header_buf + 0x2a, &bmi_.bmiHeader.biYPelsPerMeter, 4);
    memcpy(header_buf + 0x2e, &bmi_.bmiHeader.biClrUsed,       4);
    memcpy(header_buf + 0x32, &bmi_.bmiHeader.biClrImportant,  4);
}

void CImageDIB::PrintBitmapHeader() {
    printf("bfType          = %x\n", bmfh_.bfType);
    printf("bfSize          = %x\n", bmfh_.bfSize);
    printf("bfReserved1     = %x\n", bmfh_.bfReserved1);
    printf("bfReserved2     = %x\n", bmfh_.bfReserved2);
    printf("bfOffBits       = %x\n", bmfh_.bfOffBits);
    printf("biSize          = %x\n", bmi_.bmiHeader.biSize);
    printf("biWidth         = %x\n", bmi_.bmiHeader.biWidth);
    printf("biHeight        = %x\n", bmi_.bmiHeader.biHeight);
    printf("biPlanes        = %x\n", bmi_.bmiHeader.biPlanes);
    printf("biBitCount      = %x\n", bmi_.bmiHeader.biBitCount);
    printf("biCompression   = %x\n", bmi_.bmiHeader.biCompression);
    printf("biSizeImage     = %x\n", bmi_.bmiHeader.biSizeImage);
    printf("biXPelsPerMeter = %x\n", bmi_.bmiHeader.biXPelsPerMeter);
    printf("biYPelsPerMeter = %x\n", bmi_.bmiHeader.biYPelsPerMeter);
    printf("biClrUsed       = %x\n", bmi_.bmiHeader.biClrUsed);
    printf("biClrImportant  = %x\n", bmi_.bmiHeader.biClrImportant);
}
