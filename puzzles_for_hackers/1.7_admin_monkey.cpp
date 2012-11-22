#include <iostream>
#include <cstdio>
using namespace std;

int main () {
    char pass0[][10] = {
        "w&G4kP%jC",
        "9JM>u*1HQ",
        "+Bir3Zs8#",
        "A@=f[Lut5",
        "E8Kp?2{ny",
    };

    char pass1[][11] = {
        "D5fq$3+JP",
        "aE#k19hjW",
        "$oqXC3t0S",
        "29W&f8Vc*",
        "Ra<12j9#T",
    };

    char pass2[][11] = {
        "fL2ffh*fL",
        "5/veQ53vv",
        "J97!jH7!j",
        "$YY3@m43Y",
        "U*66j*KU6",
    };

    cout << "pass0" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%4d", pass0[i][j]);
        }
        cout << endl;
    }

    cout << "pass1" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%4d", pass1[i][j]);
        }
        cout << endl;
    }

    cout << "pass2" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%4d", pass2[i][j]);
        }
        cout << endl;
    }

}
