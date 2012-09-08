#include <algorithm>
#include "graphics.h"

CPolyVertex::CPolyVertex() {
}

CPolyVertex::~CPolyVertex() {
    Clear();
}

void CPolyVertex::Clear() {
    data_.clear();
}

bool CPolyVertex::Add(double x, double y) {
    FPOINT p;
    p.x = x;
    p.y = y;
    data_.push_back(p);
    return true;
}

void CPolyVertex::Get(FPOINT **v, int index) {
    *v = &data_[index];
}


CPolySide::CPolySide() {
}

CPolySide::~CPolySide() {
    Clear();
}

void CPolySide::Clear() {
    data_.clear();
}

bool CPolySide::Add(FPOINT *v1, FPOINT *v2) {
    TPolySide s;
    s.v1 = v1;
    s.v2 = v2;
    data_.push_back(s);
    return true;
}

void CPolySide::Get(FPOINT **v1, FPOINT **v2, int index) {
    *v1 = data_[index].v1;
    *v2 = data_[index].v2;
}

bool CPolySide::IntersectoinX(int index, double y, double *x) {
    FPOINT *v1, *v2;
    Get(&v1, &v2, index);

    if (v1->y == v2->y) return true;

    if ((v1->y <= y && y <= v2->y) || (v2->y <= y && y <= v1->y)) {
        if (y == v1->y) {
            *x = v1->x;
            return true;
        }
        if (y == v2->y) {
            *x = v2->x;
            return true;
        }

        if (v2->y < v1->y) {
            std::swap(v1, v2);
        }

        *x = v1->x + (y - v1->y) * (v2->x - v1->x) / (v2->y - v1->y);
        return true;
    }

    return false;
}


bool DrawCircle(CImage32 *dst, double mx, double my, double r, DWORD color) {
    for (int y = my - r, y_last = my + r; y <= y_last; y++) {
        for (int x = mx - r, x_last = mx + r; x <= x_last; x++) {
            if ((x - mx) * (x - mx) + (y - my) * (y - my) <= r * r) {
                dst->PixelSet(x, y, color);
            }
        }
    }
    return true;
}

bool InTriangle(double x, double y, CVector2* p0, CVector2 *p1, CVector2 *p2) {
    double vx0, vy0, vx1, vy1, z;

    vx0 = p1->x - p0->x;
    vy0 = p1->y - p0->y;
    vx1 = x - p1->x;
    vy1 = y - p1->y;
    z = vx0 * vy1 - vx1 * vy0;
    if (z < 0) return false;

    vx0 = p2->x - p1->x;
    vy0 = p2->y - p1->y;
    vx1 = x - p2->x;
    vy1 = y - p2->y;
    z = vx0 * vy1 - vx1 * vy0;
    if (z < 0) return false;


    vx0 = p0->x - p2->x;
    vy0 = p0->y - p2->y;
    vx1 = x - p0->x;
    vy1 = y - p0->y;
    z = vx0 * vy1 - vx1 * vy0;
    if (z < 0) return false;

    return true;
}

bool DrawTriangle(CImage32 *dst, TTrianglePos *tri, DWORD color, DWORD alpha) {
    int min_y = std::min(tri->p[0].y, std::min(tri->p[1].y, tri->p[2].y));
    int max_y = std::max(tri->p[0].y, std::max(tri->p[1].y, tri->p[2].y));

    if (max_y < 0 || dst->Height() <= min_y) return false;

    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, dst->Height() - 1);

    CPolySide ps;
    for (int i = 0; i < 3; i++) {
        FPOINT *v1 = &tri->p[i];
        FPOINT *v2 = &tri->p[(i+1) % 3];
        ps.Add(v1, v2);
    }

    for (int y = min_y; y <= max_y; y++) {
        double edges[2];
        int edges_num = 0;

        for (int i = 0; i < ps.Num(); i++) {
            const double kVertexDiff = 0.125;
            double x;
            if (ps.IntersectoinX(i, y + kVertexDiff, &x)) {
                edges[edges_num++] = x;
                if (edges_num > 2) {
                    return false;
                }
            }
        }
        if (edges_num != 2) {
            continue;
        }

        int first = edges[0] + 0.5;
        int last = edges[1] + 0.5;
        if (first == last) {
            continue;
        }
        if (last < first) {
            std::swap(first, last);
        }
        first = std::max(first, 0);
        last = std::min(last, dst->Width() - 1);

        dst->DrawXLine(first, last, y, color, alpha);
    }

    return true;
}
