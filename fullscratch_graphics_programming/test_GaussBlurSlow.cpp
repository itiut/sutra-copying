/* -*- compile-command: "g++ -Wall -Wextra -O2 test_GaussBlurSlow.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp lib/filters.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/filters.h"
using namespace std;

void Test_GaussBlurSlow(const char *filename) {
    CImageDIB src(filename);
    CImageDIB temp(src.Width(), src.Height());
    CImageDIB dst(src.Width(), src.Height());

    GaussBlurXSlow(&temp, &src, 5);
    GaussBlurYSlow(&dst, &temp, 5);

    dst.WriteBitmap("output_GaussBlurSlow.bmp");
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_GaussBlurSlow(argv[1]);

    return 0;
}
