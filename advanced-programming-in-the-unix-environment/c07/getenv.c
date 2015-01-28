#include "apue.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        err_quit("usage: %s NAME...", argv[0]);
    }

    for (int i = 1; i < argc; i++) {
        char *val;
        if ((val = getenv(argv[i])) == NULL) {
            printf("not found: %s\n", argv[i]);
            continue;
        }
        printf("%s = %s\n", argv[i], val);
    }
    return 0;
}
