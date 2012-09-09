#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "bitmap.h"
#include "img32.h"

class CBezier {
protected:
    double p_[4];

public:
    CBezier();
    void SetParams(double p0, double p1, double p2, double p3);
    void GetParams(double *p0, double *p1, double *p2, double *p3) const;

    double GetPos(double t) const;
    void GetRange(double *min_val, double *max_val) const;
};


double BezierLength(const CBezier *bx, const CBezier *by, int div);
void DrawBezierLine(CImage32 *dst, DWORD color, const CBezier *bx, const CBezier *by);

#endif /* _SHAPES_H_ */
