#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "bitmap.h"
#include "img32.h"

void BltWave(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t);

void BltWaveFast(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t);

void BltWave2(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t, double rx2, double ry2, double nx2, double ny2, double t2);

void BltRot(CImage32 *dst, const CImage32 *src, double rad, double zoom);

#endif /* _EFFECTS_H_ */
