/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawPolygonNonZero.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp lib/graphics.cpp" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawPolygonNonZero() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    CPolyVertex vertexes;
    vertexes.Add(150,  30);
    vertexes.Add( 75, 225);
    vertexes.Add(270, 120);
    vertexes.Add( 45,  75);
    vertexes.Add(195, 270);

    // DrawPolygon(&dib, &vertexes, 0, 255);
    DrawPolygonNonZero(&dib, &vertexes, 0, 255);

    dib.WriteBitmap("output_DrawPolygonNonZero.bmp");
}

int main () {
    Test_DrawPolygonNonZero();
}
