#ifndef _BLT_H_
#define _BLT_H_

#include "bitmap.h"

struct TClipSize {
    int width, height;
};

struct TClipBltInfo {
    int sw, sh;
    int sx, sy;
    int dx, dy;
};

struct TClipFillInfo {
    int dx, dy;
    int dw, dh;
};

enum TFilterType {
    FLT_AND,
    FLT_OR,
    FLT_XOR,
    FLT_NOT,
};

enum TBltType {
    BLT_COPY,
    BLT_NORMAL,
    BLT_ALPHA,
    BLT_KEY,
    BLT_ADD,
    BLT_MUL,
};

class CBltInfo {
public:
    TBltType type;
    BYTE alpha;
    DWORD colorkey;

    CBltInfo() {
        Clear();
    }
    void Clear() {
        type = BLT_COPY;
        alpha = 255;
        colorkey = 0;
    }
};

bool ClipBltInfo(TClipSize *dst, TClipSize *src, TClipBltInfo *info);
bool ClipFillInfo(TClipSize *dst, TClipFillInfo *info);

void PixelSet(DWORD *dst_addr, const DWORD *src_addr, BYTE src_alpha);
void PixelSetAdd(DWORD *dst_addr, const DWORD *src_addr, BYTE src_alpha);
void PixelSetMul(DWORD *dst_addr, const DWORD *src_addr, BYTE src_alpha);

void FillNormal(DWORD *dst_addr, int width, DWORD color, BYTE alpha);

void BltCopy(DWORD *dst_addr, const DWORD *src_addr, int witdh);
void BltNormal(DWORD *dst_addr, const DWORD *src_addr, int width, BYTE alpha);
void BltNormalAlpha(DWORD *dst_addr, const DWORD *src_addr, int width, BYTE alpha);
void BltKey(DWORD *dst_addr, const DWORD *src_addr, int width, BYTE alpha, DWORD colorkey);
void BltAdd(DWORD *dst_addr, const DWORD *src_addr, int width, BYTE alpha);
void BltMul(DWORD *dst_addr, const DWORD *src_addr, int width, BYTE alpha);

#endif /* _BLT_H_ */
