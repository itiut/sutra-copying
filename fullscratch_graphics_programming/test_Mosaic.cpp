/* -*- compile-command: "g++ -Wall -Wextra -O2 test_Mosaic.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/filters.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/filters.h"
using namespace std;

void Test_Mosaic(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    Mosaic(&dst, &src, 0, 0, dst.Width(), dst.Height(), 8);

    dst.WriteBitmap("output_Mosaic.bmp");
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_Mosaic(argv[1]);

    return 0;
}
