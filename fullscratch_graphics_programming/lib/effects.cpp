#include <cstdio>
#include <cmath>
#include "effects.h"

void BltWave(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t) {
    int w = src->Width();
    int h = src->Height();

    for (int cy = 0; cy < h; cy++) {
        for (int cx = 0; cx < w; cx++) {
            double tx = (double) M_PI * cy / h;
            double ty = (double) M_PI * cx / w;
            int dx = rx * cos(nx * (t + tx));
            int dy = ry * sin(ny * (t + ty));

            int x = cx + dx;
            int y = cy + dy;
            if (x < 0) x += w;
            if (y < 0) y += h;
            if (x >= w) x -= w;
            if (y >= h) y -= h;

            DWORD pixel = src->PixelGet(x, y);
            dst->PixelSet(cx, cy, pixel);
        }
    }
}

void BltWaveFast(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t) {
    int w = src->Width();
    int h = src->Height();

    int *dxs = new int[h];
    int *dys = new int[w];

    for (int i = 0; i < h; i++) {
        double tx = (double) M_PI * i / h;
        dxs[i] = rx * cos(nx * (t + tx));
    }
    for (int i = 0; i < w; i++) {
        double ty = (double) M_PI * i / w;
        dys[i] = ry * sin(ny * (t + ty));
    }

    for (int cy = 0; cy < h; cy++) {
        for (int cx = 0; cx < w; cx++) {
            int dx = dxs[cy];
            int dy = dys[cx];
            DWORD pixel = src->PixelGet(cx + dx, cy + dy);
            dst->PixelSet(cx, cy, pixel);
        }
    }

    delete[] dxs;
    delete[] dys;
}

void BltWave2(CImage32 *dst, const CImage32 *src, double rx, double ry, double nx, double ny, double t, double rx2, double ry2, double nx2, double ny2, double t2) {
    int w = src->Width();
    int h = src->Height();

    int *dxs  = new int[h];
    int *dxs2 = new int[w];
    int *dys  = new int[w];
    int *dys2 = new int[h];

    for (int x = 0; x < w; x++) {
        double rad = (double) M_PI * x / w;
        dys[x] = ry * cos(ny * (t + rad));
        dxs2[x] = ry2 * cos(ny2 * (t2 + rad));
    }
    for (int y = 0; y < h; y++) {
        double rad = (double) M_PI * y / h;
        dxs[y] = rx * cos(nx * (t + rad));
        dys2[y] = rx2 * cos(nx2 * (t2 + rad));
    }

    for (int cy = 0; cy < h; cy++) {
        for (int cx = 0; cx < w; cx++) {
            int dx = dxs[cy] + dxs2[cx];
            int dy = dys[cx] + dys2[cy];

            int x = cx + dx;
            int y = cy + dy;
            if (x < 0) x += w;
            if (y < 0) y += h;
            if (x >= w) x -= w;
            if (y >= h) y -= h;

            DWORD pixel = src->PixelGet(x, y);
            dst->PixelSet(cx, cy, pixel);
        }
    }

    delete[] dxs;
    delete[] dxs2;
    delete[] dys;
    delete[] dys2;
}

void BltRot(CImage32 *dst, const CImage32 *src, double rad, double zoom) {
    int sw = src->Width();
    int sh = src->Height();
    int dw = dst->Width();
    int dh = dst->Width();

    double baseU = 0.0;
    double baseV = 0.0;

    double deltaXU = zoom * cos(rad);
    double deltaXV = zoom * sin(rad);

    double deltaYU = zoom * cos(rad + M_PI / 2.0);
    double deltaYV = zoom * sin(rad + M_PI / 2.0);

    for (int y = 0; y < dh; y++) {
        for (int x = 0; x < dw; x++) {
            int sx = (baseU + x * deltaXU);
            int sy = (baseV + x * deltaXV);

            if (sx < 0) {
                sx = sw - (-sx) % sw;
            } else {
                sx = sx % sw;
            }
            if (sy < 0) {
                sy = sh - (-sy) % sh;
            } else {
                sy = sy % sh;
            }

            DWORD pixel = src->PixelGet(sx, sy);
            dst->PixelSet(x, y, pixel);
        }
        baseU += deltaYU;
        baseV += deltaYV;
    }
}

void BltRotAA(CImage32 *dst, const CImage32 *src, double rad, double zoom) {
    int sw = src->Width();
    int sh = src->Height();
    int dw = dst->Width();
    int dh = dst->Width();

    double baseU = 0.0;
    double baseV = 0.0;

    double deltaXU = zoom * cos(rad);
    double deltaXV = zoom * sin(rad);

    double deltaYU = zoom * cos(rad + M_PI / 2.0);
    double deltaYV = zoom * sin(rad + M_PI / 2.0);

    for (int y = 0; y < dh; y++) {
        for (int x = 0; x < dw; x++) {
            double fx = (baseU + x * deltaXU);
            double fy = (baseV + x * deltaXV);

            if (fx < 0) {
                fx = sw - fmod(-fx, sw);
            } else {
                fx = fmod(fx, sw);
            }
            if (fy < 0) {
                fy = sh - fmod(-fy, sh);
            } else {
                fy = fmod(fy, sh);
            }

            DWORD pixel = src->PixelGetAA(fx, fy);
            dst->PixelSet(x, y, pixel);
        }
        baseU += deltaYU;
        baseV += deltaYV;
    }
}
