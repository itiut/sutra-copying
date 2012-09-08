#include "graphics.h"

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
