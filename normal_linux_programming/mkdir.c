#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (mkdir(argv[i], 0777) < 0) {
            perror(argv[i]);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
