/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawPolygon.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp lib/graphics.cpp" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawPolygon() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CPolyVertex vertexes;
    vertexes.Add(60, 240);
    vertexes.Add(90, 75);
    vertexes.Add(150, 180);
    vertexes.Add(240, 30);
    vertexes.Add(270, 270);

    DrawPolygon(&dib, &vertexes, 0, 255);

    dib.WriteBitmap("output_DrawPolygon.bmp");
}

int main () {
    Test_DrawPolygon();
}
