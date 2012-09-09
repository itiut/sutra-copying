/* -*- compile-command: "g++ -Wall -Wextra -O2 test_BltRot.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/effects.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/effects.h"
using namespace std;

void Test_BltRot(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    BltRot(&dst, &src, 0.2, 1.5);

    dst.WriteBitmap("output_BltRot.bmp");
}


int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_BltRot(argv[1]);

    return 0;
}
