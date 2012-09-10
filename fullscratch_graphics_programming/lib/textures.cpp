#include <algorithm>
#include "img32.h"
#include "graphics.h"
#include "textures.h"

CTexMapVertex::CTexMapVertex() {
    Clear();
}

void CTexMapVertex::Clear() {
    num_ = 0;
}

bool CTexMapVertex::Add(double dx, double dy, double sx, double sy) {
    if (num_ >= kMaxVertex) {
        return false;
    }

    vertex_[num_].dx = dx;
    vertex_[num_].dy = dy;
    vertex_[num_].sx = sx;
    vertex_[num_].sy = sy;
    num_++;

    return true;
}

void CTexMapVertex::GetDst(double *dx, double *dy, int index) const {
    *dx = vertex_[index].dx;
    *dy = vertex_[index].dy;
}


CTexMapSide::CTexMapSide() {
    num_ = 0;
}

bool CTexMapSide::Add(TTexMapVertex *v1, TTexMapVertex *v2) {
    if (num_ >= kMaxSide) {
        return false;
    }

    side_[num_].v1 = v1;
    side_[num_].v2 = v2;
    num_++;

    return true;
}

void CTexMapSide::Get(TTexMapVertex **v1, TTexMapVertex **v2, int index) {
    *v1 = side_[index].v1;
    *v2 = side_[index].v2;
}

bool CTexMapSide::Intersection(int index, double y, double *x, double *sx, double *sy) {
    if (index < 0 || num_ <= index) {
        return false;
    }

    TTexMapVertex *v1 = side_[index].v1;
    TTexMapVertex *v2 = side_[index].v2;

    if (v1->dy == v2->dy) {
        return false;
    }
    if ((y < v1->dy && y < v2->dy) || (y > v1->dy && y > v2->dy)) {
        return false;
    }

    if (y == v1->dy) {
        *x = v1->dx;
        *sx = v1->sx;
        *sy = v1->sy;
        return true;
    } else if (y == v2->dy) {
        *x = v2->dx;
        *sx = v2->sx;
        *sy = v2->sy;
        return true;
    }

    if (v2->dy < v1->dy) {
        std::swap(v1, v2);
    }

    *x  = v1->dx + (v2->dx - v1->dx) * (y - v1->dy) / (v2->dy - v1->dy);
    *sx = v1->sx + (v2->sx - v1->sx) * (y - v1->dy) / (v2->dy - v1->dy);
    *sy = v1->sy + (v2->sy - v1->sy) * (y - v1->dy) / (v2->dy - v1->dy);

    return true;
}


bool Texmap(CImage32 *dst, const CImage32 *src, CTexMapVertex *vertex, BYTE alpha) {
    int num = vertex->Num();
    if (num < 3) {
        return false;
    }

    int min_y = dst->Height() - 1;
    int max_y = 0;

    for (int i = 0; i < num; i++) {
        double dx, dy;
        vertex->GetDst(&dx, &dy, i);
        if (i == 0) {
            min_y = max_y = dy;
        } else {
            min_y = std::min(min_y, (int) dy);
            max_y = std::max(max_y, (int) dy);
        }
    }

    min_y = std::max(min_y, 0);
    max_y = std::min(max_y, dst->Height() - 1);

    CTexMapSide tms;
    for (int i = 0; i < num; i++) {
        tms.Add(vertex->Vertex(i), vertex->Vertex((i+1) % num));
    }

    for (int y = min_y; y <= max_y; y++) {
        double edges[2], sx[2], sy[2];
        int edges_num = 0;

        for (int i = 0; i < tms.Num(); i++) {
            const double kVertexDiff = 0.125;

            double x, sx_, sy_;
            if (tms.Intersection(i, y + kVertexDiff, &x, &sx_, &sy_)) {
                edges[edges_num] = x;
                sx[edges_num] = sx_;
                sy[edges_num] = sy_;
                edges_num++;
                if (edges_num == 2) {
                    break;
                }
            }
        }

        if (edges_num != 2) {
            continue;
        }
        if (edges[0] == edges[1]) {
            continue;
        }

        if (edges[1] < edges[0]) {
            std::swap(edges[0], edges[1]);
            std::swap(sx[0], sx[1]);
            std::swap(sy[0], sy[1]);
        }

        double du = (sx[1] - sx[0]) / (edges[1] - edges[0]);
        double dv = (sy[1] - sy[0]) / (edges[1] - edges[0]);

        if (edges[0] < 0) {
            sx[0] += du * (-edges[0]);
            sy[0] += dv * (-edges[0]);
            edges[0] = 0.0;
        }
        edges[1] = std::min(edges[1], (double) dst->Width());

        DWORD *dst_addr = (DWORD *) dst->PixelAddressNC(edges[0], y);
        for (int x = edges[0], x_end = edges[1]; x < x_end; x++, dst_addr++) {
            // fast
            // DWORD *src_addr = (DWORD *) src->PixelAddressNC(sx[0], sy[0]);
            // *dst_addr = *src_addr;

            // slow
            DWORD c = src->PixelGetAA(sx[0], sy[0]);
            dst->PixelSet(x, y, c, alpha);

            sx[0] += du;
            sy[0] += dv;
        }
    }

    return true;
}

bool Texmap(CImage32 *dst, int mx, int my, double angle, double mul, const CImage32 *src, BYTE alpha) {
    return Texmap(dst, mx, my, angle, mul, src, 0, 0, src->Width(), src->Height(), alpha);
}

bool Texmap(CImage32 *dst, int mx, int my, double angle, double mul, const CImage32 *src, int sx, int sy, int sw, int sh, BYTE alpha) {
    int w = sw / 2;
    int h = sh / 2;

    CVector2 v[4];
    v[0].Set(-w, -h);
    v[1].Set( w, -h);
    v[2].Set( w,  h);
    v[3].Set(-w,  h);

    for (int i = 0; i < 4; i++) {
        v[i].Mul(mul);
        v[i].Rotate(angle);
        v[i].x += mx;
        v[i].y += my;
    }

    CTexMapVertex vertex;
    vertex.Add(v[0].x, v[0].y, sx, sy);
    vertex.Add(v[1].x, v[1].y, sx + sw, sy);
    vertex.Add(v[2].x, v[2].y, sx + sw, sy + sh);
    vertex.Add(v[3].x, v[3].y, sx, sy + sh);

    return Texmap(dst, src, &vertex, alpha);
}
