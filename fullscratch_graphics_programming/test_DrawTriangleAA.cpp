/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawTriangleAA.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawTriangleAASlow () {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CVector2 p[3];
    p[0].x =  30; p[0].y = 180;
    p[1].x = 180; p[1].y =  60;
    p[2].x = 270; p[2].y = 270;

    for (int y = 0; y < 300; y++) {
        for (int x = 0; x < 300; x++) {
            int c = 0;

            for (int dy = 0; dy < 5; dy++) {
                for (int dx = 0; dx < 5; dx++) {
                    if (InTriangle(x + dx / 5.0 , y + dy / 5.0, &p[0], &p[1], &p[2])) {
                        c++;
                    }
                }
            }

            if (c > 0) {
                dib.PixelSet(x, y, 0xff000000, 255 * c / 25);
            }
        }
    }

    dib.WriteBitmap("output_DrawTriangleAASlow.bmp");
}

void Test_DrawTriangleAA() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    TTrianglePos tri;
    tri.p[0].x =  30; tri.p[0].y = 180;
    tri.p[1].x = 180; tri.p[1].y =  60;
    tri.p[2].x = 270; tri.p[2].y = 270;
    DrawTriangleAA(&dib, &tri, 0xff000000, 255);

    dib.WriteBitmap("output_DrawTriangleAA.bmp");
}


int main () {
    Test_DrawTriangleAASlow();
    Test_DrawTriangleAA();
}
