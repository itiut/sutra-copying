#ifndef _FILTERS_H_
#define _FILTERS_H_

#include "bitmap.h"
#include "img32.h"

bool Mosaic(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size);
bool MosaicA(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size);

#endif /* _FILTERS_H_ */
