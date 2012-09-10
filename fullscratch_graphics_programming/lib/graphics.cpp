#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "graphics.h"

// class ColyVertex
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


// class CPolySize
CPolySide::CPolySide() {
}

CPolySide::~CPolySide() {
    Clear();
}

void CPolySide::Clear() {
    data_.clear();
}

bool CPolySide::Add(FPOINT *v1, FPOINT *v2) {
    return Add(v1, v2, true);
}

bool CPolySide::Add(FPOINT *v1, FPOINT *v2, bool upper) {
    TPolySide s;
    s.v1 = v1;
    s.v2 = v2;
    s.upper = upper;
    data_.push_back(s);
    return true;
}

void CPolySide::Get(FPOINT **v1, FPOINT **v2, int index) {
    *v1 = data_[index].v1;
    *v2 = data_[index].v2;
}

bool CPolySide::Upper(int index) const {
    return data_[index].upper;
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


// class CBezier
CBezier::CBezier() {
    p_[0] = p_[1] = p_[2] = p_[3] = 0;
}

void CBezier::SetParams(double p0, double p1, double p2, double p3) {
    p_[0] = p0;
    p_[1] = p1;
    p_[2] = p2;
    p_[3] = p3;
}

void CBezier::GetParams(double *p0, double *p1, double *p2, double *p3) const {
    *p0 = p_[0];
    *p1 = p_[1];
    *p2 = p_[2];
    *p3 = p_[3];
}

double CBezier::GetPos(double t) const {
    return (1.0 - t) * (1.0 - t) * (1.0 - t) * p_[0] + 3.0 * t * (1.0 - t) * (1.0 - t) * p_[1]
        + 3.0 * t * t * (1.0 - t) * p_[2] + t * t * t * p_[3];
}

void CBezier::GetRange(double *min_val, double *max_val) const {
    *min_val = *std::min_element(p_, p_ + 3);
    *max_val = *std::max_element(p_, p_ + 3);
}


// class CPath
CPath::CPath(double cx, double cy) {
    cx_ = cx;
    cy_ = cy;
}

CPath::~CPath() {
    Clear();
}

void CPath::Clear() {
    bx_.clear();
    by_.clear();
}

void CPath::AddSide(CBezier **bx, CBezier **by) {
    bx_.push_back(CBezier());
    by_.push_back(CBezier());
    *bx = &bx_.back();
    *by = &by_.back();
}

void CPath::AddM(double cx, double cy) {
    cx_ = cx;
    cy_ = cy;
}

void CPath::AddC(double x1, double y1, double x2, double y2, double x3, double y3) {
    CBezier *bx, *by;
    AddSide(&bx, &by);

    bx->SetParams(cx_, x1, x2, x3);
    by->SetParams(cy_, y1, y2, y3);
    cx_ = x3;
    cy_ = y3;
}

void CPath::AddV(double x2, double y2, double x3, double y3) {
    CBezier *bx, *by;
    AddSide(&bx, &by);

    bx->SetParams(cx_, cx_, x2, x3);
    by->SetParams(cy_, cy_, y2, y3);
    cx_ = x3;
    cy_ = y3;
}

void CPath::AddY(double x1, double y1, double x3, double y3) {
    CBezier *bx, *by;
    AddSide(&bx, &by);

    bx->SetParams(cx_, x1, x3, x3);
    by->SetParams(cy_, y1, y3, y3);
    cx_ = x3;
    cy_ = y3;
}

void CPath::AddL(double x3, double y3) {
    CBezier *bx, *by;
    AddSide(&bx, &by);

    bx->SetParams(cx_, cx_, x3, x3);
    by->SetParams(cy_, cy_, y3, y3);
    cx_ = x3;
    cy_ = y3;
}

void CPath::CreateVertex(CPolyVertex *vertex, double r) {
    for (int i = 0; i < (int) bx_.size(); i++) {
        CBezier *bx = &bx_[i];
        CBezier *by = &by_[i];

        double length = BezierLength(bx, by, 8);
        if (length == 0) {
            continue;
        }

        double dt = r / length;
        for (double t = 0; t < 1.0; t += dt) {
            double x = bx->GetPos(t);
            double y = by->GetPos(t);
            vertex->Add(x, y);
        }
    }
}



// function

bool DrawCircle(CImage32 *dst, double mx, double my, double r, DWORD color) {
    int min_x = mx - r, max_x = mx + r;
    int min_y = my - r, max_y = my + r;

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            if (InOriginCircle(x - mx, y - my, r)) {
                dst->PixelSet(x, y, color);
            }
        }
    }

    return true;
}

bool DrawCircleAASlow(CImage32 *dst, double mx, double my, double r, int div, DWORD color, BYTE alpha) {
    int min_x = mx - r, max_x = mx + r;
    int min_y = my - r, max_y = my + r;

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            int c = 0;
            for (int i = 0; i < div; i++) {
                for (int j = 0; j < div; j++) {
                    double dx = (double) j / div;
                    double dy = (double) i / div;
                    if (InOriginCircle(x + dx - mx, y + dy - my, r)) {
                        c++;
                    }
                }
            }

            if (c > 0) {
                int d = 255 * c / (div * div);
                dst->PixelSet(x, y, color, d * alpha / 255);
            }
        }
    }

    return true;
}

bool DrawCircleAA(CImage32 *dst, double mx, double my, double r, int div, DWORD color, BYTE alpha) {
    if (r <= 0) return false;
    if (mx + r < 0 || dst->Width() < mx - r) return false;
    if (my + r < 0 || dst->Height() < my - r) return false;

    bool small = (r <= 3) ? true : false;

    int min_x = mx - r, max_x = mx + r;
    int min_y = my - r, max_y = my + r;

    int dr = r * div;
    int dmx = mx * div;
    int dmy = my * div;

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            double fx = x - mx;
            double fy = y - my;

            bool insides[4];
            std::fill_n(insides, 4, false);

            if (small == false) {
                insides[0] = InOriginCircle(fx    , fy    , r);
                insides[1] = InOriginCircle(fx + 1, fy    , r);
                insides[2] = InOriginCircle(fx    , fy + 1, r);
                insides[3] = InOriginCircle(fx + 1, fy + 1, r);
            } else {
                insides[0] = true;
            }

            bool outside = !insides[0] && !insides[1] && !insides[2] && !insides[3];
            if (outside) {
                continue;
            }

            bool notaa = insides[0] && insides[1] && insides[2] && insides[3];
            if (notaa) {
                dst->PixelSet(x, y, color, alpha);
                continue;
            }

            int c = 0;
            for (int i = 0; i < div; i++) {
                for (int j = 0; j < div; j++) {
                    if (InOriginCircle(x * div + j - dmx, y * div + i - dmy, dr)) {
                        c++;
                    }
                }
            }

            if (c > 0) {
                int d = 255 * c / (div * div);
                dst->PixelSet(x, y, color, d * alpha / 255);
            }
        }
    }

    return true;
}


inline bool InOriginCircle(double x, double y, double r) {
    return x * x + y * y <= r * r;
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

bool DrawTriangle(CImage32 *dst, TTrianglePos *tri, DWORD color, BYTE alpha) {
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

        int first = edges[0];
        int last = edges[1];
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

bool DrawTriangleAA(CImage32 *dst, TTrianglePos *tri, DWORD color, BYTE alpha) {
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

        double first = edges[0];
        double last = edges[1];
        if (first == last) {
            continue;
        }
        if (last < first) {
            std::swap(first, last);
        }
        first = std::max(first, 0.0);
        last = std::min(last, dst->Width() - 1.0);

        dst->DrawXLineAA(first, last, y, color, alpha);
    }

    return true;
}


bool DrawPolygon(CImage32 *dst, CPolyVertex *buf, DWORD color, BYTE alpha) {
    if (buf->Num() < 3) {
        return false;
    }

    int min_y, max_y;
    for (int i = 0; i < buf->Num(); i++) {
        FPOINT *p;
        buf->Get(&p, i);
        if (i == 0) {
            min_y = max_y = p->y;
            continue;
        }
        min_y = std::min(min_y, (int) p->y);
        max_y = std::max(max_y, (int) p->y);
    }

    if (max_y < 0 || dst->Height() <= min_y) {
        return false;
    }

    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, dst->Height() - 1);

    CPolySide ps;
    for (int i = 0; i < buf->Num(); i++) {
        FPOINT *v1, *v2;
        buf->Get(&v1, i);
        buf->Get(&v2, (i+1) % buf->Num());
        ps.Add(v1, v2);
    }

    for (int y = min_y; y <= max_y; y++) {
        const int kMaxEdgesNum = 256;
        double edges[kMaxEdgesNum];
        int edges_num = 0;

        for (int i = 0; i < ps.Num(); i++) {
            const double kVertexDiff = 0.125;
            double x;
            if (ps.IntersectoinX(i, y + kVertexDiff, &x)) {
                edges[edges_num++] = x;
                if (edges_num >= kMaxEdgesNum) {
                    return false;
                }
            }
        }

        if (edges_num % 2 != 0 || edges_num == 0) {
            continue;
        }

        std::sort(edges, edges + edges_num);

        for (int i = 0; i < edges_num - 1; i += 2) {
            double left = edges[i];
            double right = edges[i + 1];

            if (left != right) {
                left = std::max(left, 0.0);
                right = std::min(right, (double) dst->Width());

                dst->DrawXLine(left, right, y, color, alpha);
            }
        }
    }

    return true;
}

bool DrawPolygonNonZero(CImage32 *dst, CPolyVertex *buf, DWORD color, BYTE alpha) {
    if (buf->Num() < 3) {
        return false;
    }

    int min_y, max_y;
    for (int i = 0; i < buf->Num(); i++) {
        FPOINT *p;
        buf->Get(&p, i);
        if (i == 0) {
            min_y = max_y = p->y;
            continue;
        }
        min_y = std::min(min_y, (int) p->y);
        max_y = std::max(max_y, (int) p->y);
    }

    if (max_y < 0 || dst->Height() <= min_y) {
        return false;
    }

    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, dst->Height() - 1);

    CPolySide ps;
    for (int i = 0; i < buf->Num(); i++) {
        FPOINT *v1, *v2;
        buf->Get(&v1, i);
        buf->Get(&v2, (i+1) % buf->Num());

        bool upper = v2->y > v1->y;
        ps.Add(v1, v2, upper);
    }

    for (int y = min_y; y <= max_y; y++) {
        const int kMaxEdgesNum = 256;
        double edges[kMaxEdgesNum];
        bool upper[kMaxEdgesNum];
        int edges_num = 0;

        for (int i = 0; i < ps.Num(); i++) {
            const double kVertexDiff = 0.125;
            double x;
            if (ps.IntersectoinX(i, y + kVertexDiff, &x)) {
                edges[edges_num] = x;
                upper[edges_num] = ps.Upper(i);
                edges_num++;
                if (edges_num >= kMaxEdgesNum) {
                    return false;
                }
            }
        }

        if (edges_num % 2 != 0 || edges_num == 0) {
            continue;
        }

        for (int i = 1; i < edges_num; i++) {
            double temp_x = edges[i];
            bool temp_upper = upper[i];
            if (edges[i - 1] > temp_x) {
                int j = i;
                do {
                    edges[j] = edges[j - 1];
                    upper[j] = upper[j - 1];
                    j--;
                } while (j > 0 && edges[j - 1] > temp_x);
                edges[j] = temp_x;
                upper[j] = temp_upper;
            }
        }

        for (int i = 0; i < edges_num - 1; i++) {
            double left = edges[i];
            double right = edges[i + 1];

            if (left != right) {
                int counter = 0;
                for (int j = 0; j <= i; j++) {
                    if (upper[j]) {
                        counter++;
                    } else {
                        counter--;
                    }
                }

                if (counter != 0) {
                    left = std::max(left, 0.0);
                    right = std::min(right, (double) dst->Width());
                    dst->DrawXLine(left, right, y, color, alpha);
                }
            }
        }
    }

    return true;
}

double BezierLength(const CBezier *bx, const CBezier *by, int div) {
    double length = 0.0;
    double t = 0.0;
    double dt = 1.0 / div;

    for (int i = 0; i < div; i++) {
        double x0 = bx->GetPos(t);
        double y0 = by->GetPos(t);
        double x1 = bx->GetPos(t + dt);
        double y1 = by->GetPos(t + dt);

        double len_square = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
        if (len_square != 0) {
            length += sqrt(len_square);
        }

        t += dt;
    }

    return length;
}

void DrawBezierLine(CImage32 *dst, DWORD color, const CBezier *bx, const CBezier *by) {
    double length = BezierLength(bx, by, 8);
    if (length == 0) {
        return;
    }

    double dt = 4.0 / length;
    for (double t = 0.0; t < 1.0; t += dt) {
        double x0 = bx->GetPos(t);
        double y0 = by->GetPos(t);
        double x1 = bx->GetPos(t + dt);
        double y1 = by->GetPos(t + dt);

        dst->DrawLine(x0, y0, x1, y1, color);
    }
}
