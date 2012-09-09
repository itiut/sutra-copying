#include <cmath>
#include <algorithm>
#include "shapes.h"

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
