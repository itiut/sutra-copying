#include <iostream>
using namespace std;

class Alphametic {
public:
    int H, A, C, K, E, R, N, G, Y;

    void make_1st();
    void make_2nd(int c);
    void make_3rd(int c);
    void make_4th(int c);
    void make_5th(int c);
    void make_6th(int c);
    void show();
};

void Alphametic::make_1st() {
    for (int i = 1; i < 10; i++) {
        int y = (3 * i) % 10;
        if (y == i) {
            continue;
        }
        R = i;
        Y = y;
        make_2nd((3 * R) / 10);
    }
}

void Alphametic::make_2nd(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == R || i == Y) {
            continue;
        }
        int g = (3 * i + c) % 10;
        if (g == i || g == R || g == Y) {
            continue;
        }
        E = i;
        G = g;
        make_3rd((3 * E + c) / 10);
    }
}

void Alphametic::make_3rd(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == R || i == Y || i == E || i == G) {
            continue;
        }
        int r = (3 * i + c) % 10;
        if (r != R) {
            continue;
        }
        K = i;
        make_4th((3 * K + c) / 10);
    }
}

void Alphametic::make_4th(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == R || i == Y || i == E || i == G || i == K) {
            continue;
        }
        int e = (3 * i + c) % 10;
        if (e != E) {
            continue;
        }
        C = i;
        make_5th((3 * C + c) / 10);
    }
}

void Alphametic::make_5th(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == R || i == Y || i == E || i == G || i == K || i == C) {
            continue;
        }
        int n = (3 * i + c) % 10;
        if (n == i || n == R || n == Y || n == E || n == G || n == K || n == C) {
            continue;
        }
        A = i;
        N = n;
        make_6th((3 * A + c) / 10);
    }
}

void Alphametic::make_6th(int c) {
    for (int i = 1; i < 4; i++) {
        if (i == R || i == Y || i == E || i == G || i == K || i == C || i == A || i == N) {
            continue;
        }
        int e = (3 * i + c) % 10;
        if (e != E || (3 * i + c) / 10 > 0) {
            continue;
        }
        H = i;
        show();
    }
}

void Alphametic::show() {
    cout << H << A << C << K << E << R << " + "
         << H << A << C << K << E << R << " + "
         << H << A << C << K << E << R << " = "
         << E << N << E << R << G << Y << endl;
}


int main () {
    cout << "HACKER + HACKER + HACKER = ENERGY" << endl;
    Alphametic map;
    map.make_1st();
}
