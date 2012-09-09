/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawCircle.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cmath>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawCircle () {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    DrawCircle(&dib, 150, 150, 100, 0);
    DrawCircle(&dib, 0, 0, 30, 0);
    dib.WriteBitmap("output_DrawCircle.bmp");
}

void DrawPolyCircle(CImage32 *dst, double mx, double my, double r, DWORD color) {
    const int kPolyCircle_MaxDiv = 512;

    double len = 2.0 * M_PI / r;

    int n = len / 4.0;
    if (n < 32) n = 32;
    if (n > kPolyCircle_MaxDiv) n = kPolyCircle_MaxDiv;

    CPolyVertex pv;
    for (int i = 0; i < n; i++) {
        double rad = 2.0 * M_PI * i / n;
        pv.Add(mx + r * cos(rad), my + r * sin(rad));
    }

    DrawPolygon(dst, &pv, color, 255);
}

void Test_DrawPolyCircle() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    DrawPolyCircle(&dib, 150, 150, 100, 0);
    dib.WriteBitmap("output_DrawPolyCircle.bmp");
}

int main () {
    Test_DrawCircle();
    Test_DrawPolyCircle();
}
