/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawTriangle.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp lib/graphics.cpp" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawTriangle1 () {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CVector2 p[3];
    p[0].x =  20; p[0].y = 120;
    p[1].x = 120; p[1].y =  40;
    p[2].x = 180; p[2].y = 180;

    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 200; x++) {
            if (InTriangle(x, y, &p[0], &p[1], &p[2])) {
                dib.PixelSet(x, y, 0xff000000);
            }
        }
    }

    dib.WriteBitmap("output_DrawTriangle1.bmp");
}

void Test_DrawTriangle2() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    TTrianglePos tri;
    tri.p[0].x =  20; tri.p[0].y = 120;
    tri.p[1].x = 120; tri.p[1].y =  40;
    tri.p[2].x = 180; tri.p[2].y = 180;
    DrawTriangle(&dib, &tri, 0xff000000, 255);

    dib.WriteBitmap("output_DrawTriangle2.bmp");
}

int main () {
    Test_DrawTriangle1();
    Test_DrawTriangle2();
}
