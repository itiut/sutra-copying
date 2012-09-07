#ifndef _BLT_H_
#define _BLT_H_

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

#endif /* _BLT_H_ */
