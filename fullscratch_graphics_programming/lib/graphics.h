#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <vector>
#include "bitmap.h"
#include "img32.h"

class CVector2 {
public:
    double x, y;

    CVector2(const CVector2& src) { x = src.x; y = src.y; }
    CVector2() { x = 0; y = 0; }
    CVector2(double setx, double sety) { x = setx; y = sety; }
};


struct FPOINT {
    double x, y;
};

struct TPolySide {
    FPOINT *v1;
    FPOINT *v2;
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

    int Num() { return data_.size(); };
};

class CPolySide {
protected:
    std::vector<TPolySide> data_;

public:
    CPolySide();
    ~CPolySide();

    void Clear();
    bool Add(FPOINT *v1, FPOINT *v2);
    void Get(FPOINT **v1, FPOINT **v2, int index);

    bool IntersectoinX(int index, double y, double *x);

    int Num() { return data_.size(); }
};


bool DrawCircle(CImage32 *dst, double mx, double my, double r, DWORD color);

bool InTriangle(double x, double y, CVector2* p0, CVector2 *p1, CVector2 *p2);

bool DrawTriangle(CImage32 *dst, TTrianglePos *tri, DWORD color, DWORD alpha);

#endif /* _GRAPHICS_H_ */
