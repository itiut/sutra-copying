#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main (int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <key>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ifstream ifs(argv[1]);

    string out;
    ifs >> out;
    string key(argv[2]);

    for (int i = 0, size = out.length(); i < size; i++) {
        char c = key[i % key.length()] ^ out[i];
        cout << c;
    }
    cout << endl;
}
