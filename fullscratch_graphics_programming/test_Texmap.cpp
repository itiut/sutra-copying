/* -*- compile-command: "g++ -Wall -Wextra -O2 test_Texmap.cpp lib/img32.cpp lib/imgdib.cpp lib/blt.cpp lib/graphics.cpp lib/textures.cpp -lm" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/textures.h"
using namespace std;

void Test_Texmap(const char *filename) {
    CImageDIB src(filename);
    CImageDIB dst(src.Width(), src.Height());
    dst.PixelFill(0xffffffff, 255);

    Texmap(&dst, 200, 200, 0.3, 0.8, &src, 255);

    dst.WriteBitmap("output_Texmap.bmp");
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_Texmap(argv[1]);

    return 0;
}
