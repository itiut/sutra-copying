#include <iostream>
#include <string>
using namespace std;

int main () {
    string in  = "creature_creature_creature";
    string out = "]VTYJQC]aGC]_PDJ[{RJ[EEMLA";

    for (int i = 0, size = in.length(); i < size; i++) {
        char c = in[i] ^ out[i];
        cout << c;
    }
    cout << endl;

    string key = ">$18";
    string target = "Smith";

    for (int i = 0, size = target.length(); i < size; i++) {
        char c = key[i % 4] ^ target[i];
        cout << c;
    }
    cout << endl;
}
