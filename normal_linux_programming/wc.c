#include <stdio.h>
#include <stdlib.h>

static void do_wc(const char *path);
static void die(const char *s);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        do_wc(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            do_wc(argv[i]);
        }
    }
    return 0;
}

static void do_wc(const char *path) {
    FILE *fp;
    if (path == NULL) {
        fp = stdin;
    } else {
        fp = fopen(path, "r");
        if (fp == NULL) {
            die(path);
        }
    }

    int line = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            line++;
        }
    }
    if (path == NULL) {
        printf("%d\n", line);
    } else {
        printf("%d %s\n", line, path);
    }
}

static void die(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
