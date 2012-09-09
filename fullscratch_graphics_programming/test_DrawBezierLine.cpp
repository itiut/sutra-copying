/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawBezierLine.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawSimpleBezierLine() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CBezier bx, by;
    bx.SetParams(20, 160, 180, 200);
    by.SetParams(20, 60, 80, 200);

    for (int i = 0; i < 100; i++) {
        double t = i / 100.0;
        double px = bx.GetPos(t);
        double py = by.GetPos(t);
        dib.PixelSet(px, py, 0);
    }

    dib.WriteBitmap("output_DrawSimpleBezierLine.bmp");
}

void Test_DrawBezierLine() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CBezier bx, by;
    bx.SetParams(20, 160, 180, 200);
    by.SetParams(20, 60, 80, 200);

    DrawBezierLine(&dib, 0, &bx, &by);

    dib.WriteBitmap("output_DrawBezierLine.bmp");
}

int main () {
    Test_DrawSimpleBezierLine();
    Test_DrawBezierLine();
}
