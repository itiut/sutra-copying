#include "bitmap.h"
#include "img32.h"
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
