#include <stdio.h>

int main() {
    extern char **environ;

    for (char **s = environ; *s != NULL; s++) {
        printf("%s\n", *s);
    }
}
