/* -*- compile-command: "g++ -Wall -O2 test_jpeg.cpp lib/jpeg.cpp lib/imgdib.cpp lib/img32.cpp -ljpeg" -*- */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "lib/imgdib.h"
#include "lib/jpeg.h"
using namespace std;

void JpegToBmp(const string& jpeg_filename) {
    CImageDIB dib;
    LoadJpeg(&dib, jpeg_filename.c_str());

    string bmp_filename = jpeg_filename.substr(0, jpeg_filename.length() - 3) + "bmp";
    dib.WriteBitmap(bmp_filename.c_str());
}

void BmpToJpeg(const string& bmp_filename) {
    CImageDIB dib(bmp_filename.c_str());

    string jpeg_filename = bmp_filename.substr(0, bmp_filename.length() - 3) + "jpg";
    SaveJpeg24(&dib, jpeg_filename.c_str());
}

int main (int argc, char *argv[]) {
    if (argc < 2 || 3 < argc) {
        printf("Usage: %s [jpeg_filename] <[bmp_filename]>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    JpegToBmp(argv[1]);

    if (argc == 3) {
        BmpToJpeg(argv[2]);
    }
    return 0;
}
