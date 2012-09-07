/* -*- compile-command: "g++ -Wall -Wextra -O2 test_blt.cpp lib/blt.cpp" -*- */
#include <iostream>
#include <cstdio>
#include "lib/blt.h"
using namespace std;

void MakeFillInfo(int dx, int dy, int dw, int dh) {
    TClipSize dst = {240, 320};
    TClipFillInfo info = {dx, dy, dw, dh};
    bool ret = ClipFillInfo(&dst, &info);

    printf("%4d %4d %4d %4d -> %s -> %4d %4d %4d %4d\n", dx, dy, dw, dh, ret ? "T" : "F", info.dx, info.dy, info.dw, info.dh);
}


int main () {
    MakeFillInfo(0, 0, 0, 0);     // false
    MakeFillInfo(0, 0, 20, 20);   // true
    MakeFillInfo(0, 0, 300, 20);  // 300->240
    MakeFillInfo(10, 0, 300, 20); // 300->230
    MakeFillInfo(0, 0, 20, 400);  // 400->320
    MakeFillInfo(0, 10, 20, 400); // 400->310
    MakeFillInfo(250, 0, 20, 20); // false
    MakeFillInfo(0, 350, 20, 20); // false
    MakeFillInfo(-100, 0, 20, 20); // false
    MakeFillInfo(0, -100, 20, 20); // false
    MakeFillInfo(-10, 0, 30, 20);  // 30->20
    MakeFillInfo(0, -10, 20, 30);  // 30->20
}
