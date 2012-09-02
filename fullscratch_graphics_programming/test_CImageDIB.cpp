/* -*- compile-command: "g++ -Wall -O2 test_CImageDIB.cpp lib/imgdib.cpp lib/img32.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"

int main (int argc, char *argv[]) {
    if (argc != 1 && argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    CImageDIB dib1;
    dib1.WriteBitmap("dib1.bmp");

    CImageDIB dib2(33, 33);
    dib2.WriteBitmap("dib2.bmp");

    if (argc == 1) {
        return 0;
    }

    CImageDIB dib3(argv[1]);
    dib3.PrintBitmapHeader();
    dib3.WriteBitmap("dib3.bmp");

    return 0;
}
