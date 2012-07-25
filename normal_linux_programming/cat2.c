#include <stdio.h>
#include <stdlib.h>

static void do_cat(const char *path);
static void die(const char *s);
static void my_putc(const char c);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        do_cat(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            do_cat(argv[i]);
        }
    }
    return 0;
}

static void do_cat(const char *path) {
    FILE *fp;
    if (path == NULL) {
        fp = stdin;
    } else {
        fp = fopen(path, "r");
        if (fp == NULL) {
            die(path);
        }
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        switch (c) {
        case '\t':
            my_putc('\\');
            my_putc('t');
            break;
        case '\n':
            my_putc('$');
            my_putc('\n');
            break;
        default:
            my_putc(c);
            break;
        }
    }
    fclose(fp);
}

static void die(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}

static void my_putc(const char c) {
    if (putchar(c) < 0) {
        exit(EXIT_FAILURE);
    }
}
