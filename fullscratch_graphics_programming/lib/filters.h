#ifndef _FILTERS_H_
#define _FILTERS_H_

#include "bitmap.h"
#include "img32.h"

bool Mosaic(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size);
bool MosaicA(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size);

bool Blur(CImage32 *dst, const CImage32 *src, int size);
bool MotionBlur(CImage32 *dst, const CImage32 *src, int size, double rad, int quality);

bool GaussBlurXSlow(CImage32 *dst, const CImage32 *src, double ar);
bool GaussBlurYSlow(CImage32 *dst, const CImage32 *src, double ar);
bool GaussBlurSlow(CImage32 *dst, const CImage32 *src, double ar, bool x_direction);

#endif /* _FILTERS_H_ */
