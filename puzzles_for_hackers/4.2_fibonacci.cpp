#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int a[20];

int main () {
    int x = 0, y = 0;
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i < 13; i++) {
        x = a[i - 1];
        y = a[i - 2];
        a[i] = x + y;
    }

    for (int i = 0; i < 13; i++) {
        printf("a[%2d] = %d\n", i, a[i]);
    }
}
