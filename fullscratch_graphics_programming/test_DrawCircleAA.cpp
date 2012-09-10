/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawCircleAA.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cmath>
#include "lib/imgdib.h"
#include "lib/graphics.h"
using namespace std;

void Test_DrawCircleAASlow() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    DrawCircleAASlow(&dib, 150, 150, 100, 5, 0xff000000, 255);
    dib.WriteBitmap("output_DrawCircleAASlow.bmp");
}

void Test_DrawCircleAA() {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    DrawCircleAA(&dib, 150, 150, 100, 5, 0xff000000, 255);
    dib.WriteBitmap("output_DrawCircleAA.bmp");
}

int main () {
    Test_DrawCircleAASlow();
    Test_DrawCircleAA();
}
