/* -*- compile-command: "g++ -Wall -Wextra -O2 test_filter.cpp lib/imgdib.cpp lib/img32.cpp lib/blt.cpp" -*- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/blt.h"
using namespace std;

void Test_Filter(TFilterType filter, DWORD value, const char *in_filename, const char *out_filename) {
    CImageDIB dib(in_filename);
    dib.Filter(filter, value);
    dib.WriteBitmap(out_filename);
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [bmp_filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Test_Filter(FLT_AND, 0xff0000ff, argv[1], "output_filter1.bmp");
    Test_Filter(FLT_OR, 0xff0000ff, argv[1], "output_filter2.bmp");
    Test_Filter(FLT_XOR, 0xff0000ff, argv[1], "output_filter3.bmp");
    Test_Filter(FLT_NOT, 0, argv[1], "output_filter4.bmp");
    return 0;
}
