#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "bitmap.h"
#include "img32.h"

struct TTexMapVertex {
    double dx, dy;
    double sx, sy;
};

struct TTexMapSide {
    TTexMapVertex *v1;
    TTexMapVertex *v2;
};


class CTexMapVertex {
protected:
    static const int kMaxVertex = 4;

    int num_;
    TTexMapVertex vertex_[kMaxVertex];

public:
    CTexMapVertex();
    void Clear();

    bool Add(double dx, double dy, double sx, double sy);
    void GetDst(double *dx, double *dy, int index) const;

    int Num() const { return num_; }
    TTexMapVertex *Vertex(int index) { return &vertex_[index]; }
};


class CTexMapSide {
protected:
    static const int kMaxSide = 4;

    int num_;
    TTexMapSide side_[kMaxSide];

public:
    CTexMapSide();

    bool Add(TTexMapVertex *v1, TTexMapVertex *v2);
    void Get(TTexMapVertex **v1, TTexMapVertex **v2, int index);

    bool Intersection(int index, double y, double *x, double *sx, double *sy);

    int Num() const { return num_; }
};


bool Texmap(CImage32 *dst, const CImage32 *src, CTexMapVertex *vertex, BYTE alpha);
bool Texmap(CImage32 *dst, int mx, int my, double angle, double mul, const CImage32 *src, BYTE alpha);
bool Texmap(CImage32 *dst, int mx, int my, double angle, double mul, const CImage32 *src, int sx, int sy, int sw, int sh, BYTE alpha);

#endif /* _TEXTURES_H_ */
