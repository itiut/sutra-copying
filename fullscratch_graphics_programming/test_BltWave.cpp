/* -*- compile-command: "g++ -Wall -Wextra -O2 test_BltWave.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/effects.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/effects.h"
using namespace std;

void Test_BltWave(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    BltWave(&dst, &src, 20, 30, 5, 4, 0.5);

    dst.WriteBitmap("output_BltWave.bmp");
}

void Test_BltWaveFast(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    BltWave(&dst, &src, 20, 30, 5, 4, 0.5);

    dst.WriteBitmap("output_BltWaveFast.bmp");
}

void Test_BltWave2(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    BltWave2(&dst, &src, 20, 30, 5, 4, 0.5, 10, 24, 2, 4, -0.5);

    dst.WriteBitmap("output_BltWave2.bmp");
}


int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_BltWave(argv[1]);
    Test_BltWaveFast(argv[1]);
    Test_BltWave2(argv[1]);

    return 0;
}
