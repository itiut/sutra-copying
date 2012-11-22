#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char c;
    while (c = fgetc(fp), c != EOF) {
        if (isalpha(c) && islower(c)) {
            c = 'z' - (c - 'a');
        }
        cout << c;
    }

    fclose(fp);
    return 0;
}
