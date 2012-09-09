/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawShape.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawShape() {
    CImageDIB dib(256, 256);
    dib.PixelFill(0xffffffff, 255);

    CPath path(40, 40);
    path.AddC(80, 0, 140, 20, 160, 60);
    path.AddC(180, 100, 120, 160, 100, 160);
    path.AddC(80, 160, 0, 80, 40, 40);

    CPolyVertex vertex;
    path.CreateVertex(&vertex, 5);

    DrawPolygon(&dib, &vertex, 0, 255);
    dib.WriteBitmap("output_DrawShape.bmp");
}

int main () {
    Test_DrawShape();
}
