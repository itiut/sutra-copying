#include <iostream>
using namespace std;

class Alphametic {
public:
    int S, E, N, D, M, O, R, Y;

    void make_1st();
    void make_2nd(int c);
    void make_3rd(int c);
    void make_4th(int c);
    void show();
};

void Alphametic::make_1st() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == j) {
                continue;
            }

            int y = (i + j) % 10;
            if (y == i || y == j) {
                continue;
            }

            D = i;
            E = j;
            Y = y;
            make_2nd((D + E) / 10);
        }
    }
}

void Alphametic::make_2nd(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == D || i == E || i == Y) {
            continue;
        }
        for (int j = 0; j < 10; j++) {
            if (j == i || j == D || j == E || j == Y) {
                continue;
            }

            int e = (i + j + c) % 10;
            if (e != E) {
                continue;
            }

            N = i;
            R = j;
            make_3rd((N + R + c) / 10);
        }
    }
}

void Alphametic::make_3rd(int c) {
    for (int i = 0; i < 10; i++) {
        if (i == D || i == E || i == Y || i == N || i == R) {
            continue;
        }

        int n = (E + i + c) % 10;
        if (n != N) {
            continue;
        }

        O = i;
        make_4th((E + O + c) / 10);
    }
}

void Alphametic::make_4th(int c) {
    for (int i = 1; i < 10; i++) {
        if (i == D || i == E || i == Y || i == N || i == R || i == O) {
            continue;
        }
        for (int j = 1; j < 10; j++) {
            if (j == i || i == D || j == E || j == Y || j == N || j == R || j == O) {
                continue;
            }

            int o = (i + j + c) % 10;
            if (o != O) {
                continue;
            }
            int o_c = (i + j + c) / 10;
            if (o_c != j) {
                continue;
            }

            S = i;
            M = j;
            show();
        }
    }
}

void Alphametic::show() {
    cout << S << E << N << D << " + "
         << M << O << R << E << " = "
         << M << O << N << E << Y << endl;
}


int main () {
    cout << "SEND + MORE = MONEY" << endl;
    Alphametic map;
    map.make_1st();
}
