/* -*- compile-command: "g++ -Wall -Wextra -O2 test_DrawXLine.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "lib/imgdib.h"
using namespace std;

void Test_DrawXLine() {
    CImageDIB dib(255, 255);
    dib.PixelFill(0, 0, 255, 255, 0xffffffff, 255);

    for (int y = 30; y < 225; y++) {
        int x0 = rand() % 127;
        int x1 = rand() % 127 + 127;
        dib.DrawXLine(x0, x1, y, 0xff000000, 255);
    }

    dib.WriteBitmap("output_DrawXLine.bmp");
}

int main () {
    srand(time(NULL));

    Test_DrawXLine();
}
