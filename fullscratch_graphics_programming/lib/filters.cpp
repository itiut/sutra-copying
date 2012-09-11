#include <cstdio>
#include "bitmap.h"
#include "img32.h"
#include "graphics.h"
#include "filters.h"

bool Mosaic(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size) {
    dst->Blt(0, 0, src);

    for (int cy = y; cy < y + h; cy += size) {
        for (int cx = x; cx < x + w; cx += size) {
            int r, g, b, counter;
            r = g = b = counter = 0;

            TARGB color;

            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    color.ARGB = src->PixelGet(cx + dx, cy + dy);
                    r += color.R;
                    g += color.G;
                    b += color.B;
                    counter++;
                }
            }

            color.R = r / counter;
            color.G = g / counter;
            color.B = b / counter;

            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    dst->PixelSet(cx + dx, cy + dy, color.ARGB);
                }
            }
        }
    }

    return true;
}

bool MosaicA(CImage32 *dst, const CImage32 *src, int x, int y, int w, int h, int size) {
    dst->Blt(0, 0, src);

    for (int cy = y; cy < y + h; cy += size) {
        for (int cx = x; cx < x + w; cx += size) {
            int r, g, b, a, counter;
            r = g = b = a = counter = 0;

            TARGB color;

            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    color.ARGB = src->PixelGet(cx + dx, cy + dy);
                    a += color.A;
                    r += color.R * color.A;
                    g += color.G * color.A;
                    b += color.B * color.A;
                    counter++;
                }
            }

            if (a != 0) {
                color.A = a / counter;
                color.R = r / a;
                color.G = g / a;
                color.B = b / a;
            } else {
                color.ARGB = 0x00000000;
            }

            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    dst->PixelSet(cx + dx, cy + dy, color.ARGB);
                }
            }
        }
    }

    return true;
}

bool Blur(CImage32 *dst, const CImage32 *src, int size) {
    for (int y = 0; y < src->Height(); y++) {
        for (int x = 0; x < src->Width(); x++) {
            int r, g, b, counter;
            r = g = b = counter = 0;

            TARGB color;

            for (int dy = -size; dy <= size; dy++) {
                for (int dx = -size; dx <= size; dx++) {
                    color.ARGB = src->PixelGet(x + dx, y + dy);
                    r += color.R;
                    g += color.G;
                    b += color.B;
                    counter++;
                }
            }

            color.R = r / counter;
            color.G = g / counter;
            color.B = b / counter;

            dst->PixelSet(x, y, color.ARGB);
        }
    }

    return true;
}

bool MotionBlur(CImage32 *dst, const CImage32 *src, int size, double rad, int quality) {
    CVector2 v(1.0, 0.0);
    v.Rotate(rad);

    double dx = v.x / quality;
    double dy = v.y / quality;

    for (int y = 0; y < src->Height(); y++) {
        for (int x = 0; x < src->Width(); x++) {
            int r, g, b, counter;
            r = g = b = counter = 0;

            TARGB color;

            double sx = x - v.x * size;
            double sy = y - v.y * size;

            for (int i = 0, i_end = size * 2 * quality; i < i_end; i++) {
                color.ARGB = src->PixelGet(sx, sy);
                r += color.R;
                g += color.G;
                b += color.B;
                counter++;

                sx += dx;
                sy += dy;
            }

            color.R = r / counter;
            color.G = g / counter;
            color.B = b / counter;

            dst->PixelSet(x, y, color.ARGB);
        }
    }

    return true;
}

bool GaussBlurXSlow(CImage32 *dst, const CImage32 *src, double ar) {
    return GaussBlurSlow(dst, src, ar, true);
}

bool GaussBlurYSlow(CImage32 *dst, const CImage32 *src, double ar) {
    return GaussBlurSlow(dst, src, ar, false);
}

bool GaussBlurSlow(CImage32 *dst, const CImage32 *src, double ar, bool x_direction) {
    for (int y = 0; y < src->Height(); y++) {
        for (int x = 0; x < src->Width(); x++) {
            int r, g, b;
            r = g = b = 0;

            TARGB color;

            int range = ar * 3;

            for (int i = -range; i <= range; i++) {
                if (x_direction) {
                    color.ARGB = src->PixelGet(x + i, y);
                } else {
                    color.ARGB = src->PixelGet(x, y + i);
                }

                double gauss = exp(- i * i / (2 * ar * ar)) / sqrt(2.0 * M_PI * ar * ar);

                r += gauss * color.R;
                g += gauss * color.G;
                b += gauss * color.B;
            }

            color.R = r;
            color.G = g;
            color.B = b;

            dst->PixelSet(x, y, color.ARGB);
        }
    }

    return true;
}
