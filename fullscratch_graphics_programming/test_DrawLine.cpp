/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawLine.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
using namespace std;

int main () {
    CImageDIB dib(300, 300);
    dib.PixelFill(0, 0, 300, 300, 0xffffffff, 255);

    dib.DrawLine(0, 0, 100, 200, 0);
    dib.DrawLine(0, 0, 200, 100, 0);

    for (int i = 0; i < 300; i++) {
        dib.DrawLine(rand() % 300, rand() % 300, rand() % 300, rand() % 300, 0);
    }

    dib.WriteBitmap("output_DrawLine.bmp");
}
