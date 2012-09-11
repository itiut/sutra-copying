/* -*- compile-command: "g++ -Wall -Wextra -O2 test_Blur.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp lib/filters.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/filters.h"
using namespace std;

void Test_Blue(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());

    Blur(&dst, &src, 4);

    dst.WriteBitmap("output_Blur.bmp");
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_Blue(argv[1]);

    return 0;
}
