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

bool ClipBltInfo(TClipSize *src, TClipSize *dst, TClipBltInfo *info);
bool ClipFillInfo(TClipSize *dst, TClipFillInfo *info);

void PixelSet(DWORD *dst_addr, DWORD *src_addr, BYTE src_alpha);
void FillNormal(DWORD *dst_addr, int width, DWORD color, BYTE alpha);

void BltNormal(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha);
void BltKey(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha, DWORD colorkey);
void BltAdd(DWORD *dst_addr, DWORD *src_addr, int width, BYTE alpha);

#endif /* _BLT_H_ */
