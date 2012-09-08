/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawCircle.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp" -*- */
#include <iostream>
#include <cstdio>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

int main () {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    DrawCircle(&dib, 150, 150, 100, 0);
    DrawCircle(&dib, 0, 0, 30, 0);
    dib.WriteBitmap("output_DrawCircle.bmp");
}
