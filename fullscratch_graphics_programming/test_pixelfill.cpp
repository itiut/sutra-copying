/* -*- compile-command: "g++ -Wall -Wextra -O2 test_pixelfill.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
using namespace std;

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    CImageDIB dib(argv[1]);
    dib.PixelFill(10, 10, 40, 30, 0xffffffff, 128);
    dib.PixelFill(100, 100, 30, 30, 0xff0000ff, 128);
    dib.PixelFill(150, 150, 30, 30, 0xff00ff00, 128);
    dib.PixelFill(200, 200, 30, 30, 0xffff0000, 128);
    dib.WriteBitmap("output.bmp");
    return 0;
}
