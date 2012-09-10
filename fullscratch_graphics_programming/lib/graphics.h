#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <cmath>
#include <vector>
#include "bitmap.h"
#include "img32.h"

class CVector2 {
public:
    double x, y;

    CVector2(const CVector2& src) { x = src.x; y = src.y; }
    CVector2() { x = 0; y = 0; }
    CVector2(double setx, double sety) { Set(setx, sety); }

    void Set(double setx, double sety) { x = setx, y = sety; }

    void Mul(double c) { x *= c; y *= c; }
    void Rotate(double rad) {
        double cosr = cos(rad);
        double sinr = sin(rad);
        double tmpx = x * cosr - y * sinr;
        double tmpy = x * sinr + y * cosr;
        x = tmpx;
        y = tmpy;
    }
};


struct FPOINT {
    double x, y;
};

struct TPolySide {
    FPOINT *v1;
    FPOINT *v2;
    bool upper;
};

struct TTrianglePos {
    FPOINT p[3];
};


class CPolyVertex {
protected:
    std::vector<FPOINT> data_;

public:
    CPolyVertex();
    ~CPolyVertex();

    void Clear();
    bool Add(double x, double y);
    void Get(FPOINT **v, int index);

    int Num() const { return data_.size(); };
};


class CPolySide {
protected:
    std::vector<TPolySide> data_;

public:
    CPolySide();
    ~CPolySide();

    void Clear();
    bool Add(FPOINT *v1, FPOINT *v2);
    bool Add(FPOINT *v1, FPOINT *v2, bool upper);
    void Get(FPOINT **v1, FPOINT **v2, int index);
    bool Upper(int index) const;

    bool IntersectoinX(int index, double y, double *x);

    int Num() const { return data_.size(); }
};


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


class CPath {
protected:
    double cx_, cy_;

    std::vector<CBezier> bx_;
    std::vector<CBezier> by_;

    void AddSide(CBezier **bx, CBezier **by);

public:
    CPath(double cx, double cy);
    ~CPath();
    void Clear();

    void AddM(double cx, double cy);
    void AddC(double x1, double y1, double x2, double y2, double x3, double y3);
    void AddV(double x2, double y2, double x3, double y3);
    void AddY(double x1, double y1, double x3, double y3);
    void AddL(double x3, double y3);

    void CreateVertex(CPolyVertex *vertex, double r);
};


bool DrawCircle(CImage32 *dst, double mx, double my, double r, DWORD color);
bool DrawCircleAASlow(CImage32 *dst, double mx, double my, double r, int div, DWORD color, BYTE alpha);
bool DrawCircleAA(CImage32 *dst, double mx, double my, double r, int div, DWORD color, BYTE alpha);

bool InOriginCircle(double x, double y, double r);
bool InTriangle(double x, double y, CVector2* p0, CVector2 *p1, CVector2 *p2);

bool DrawTriangle(CImage32 *dst, TTrianglePos *tri, DWORD color, BYTE alpha);
bool DrawTriangleAA(CImage32 *dst, TTrianglePos *tri, DWORD color, BYTE alpha);

bool DrawPolygon(CImage32 *dst, CPolyVertex *buf, DWORD color, BYTE alpha);
bool DrawPolygonNonZero(CImage32 *dst, CPolyVertex *buf, DWORD color, BYTE alpha);

double BezierLength(const CBezier *bx, const CBezier *by, int div);
void DrawBezierLine(CImage32 *dst, DWORD color, const CBezier *bx, const CBezier *by);

#endif /* _GRAPHICS_H_ */
