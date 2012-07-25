#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static void do_cat(const char *path);
static void die(const char *s);
static void my_putc(const char c);

static bool bline = false;
static bool btab = false;

int main (int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "nt")) != -1) {
        switch (opt) {
        case 'n':
            bline = true;
            break;
        case 't':
            btab = true;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-n] [-t] [FILE ...]\n", argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (optind == argc) {
        do_cat(NULL);
    } else {
        for (int i = optind; i < argc; i++) {
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
        if (c == '\n' && bline) {
            my_putc('$');
            my_putc('\n');
        } else if (c == '\t' && btab) {
            my_putc('\\');
            my_putc('t');
        } else {
            my_putc(c);
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
