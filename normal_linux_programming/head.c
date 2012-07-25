#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_head(FILE *fp, long long nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help",  no_argument,       NULL, 'h'},
    {0, 0, 0, 0}
};

int main (int argc, char *argv[]) {
    int opt;
    long long nlines = DEFAULT_N_LINES;

    while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1) {
        switch (opt) {
        case 'n':
            nlines = atoll(optarg);
            break;
        case 'h':
            fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
            exit(EXIT_SUCCESS);
        case '?':
            fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    if (optind == argc) {
        do_head(stdin, nlines);
    } else {
        for (int i = optind; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                exit(EXIT_FAILURE);
            }
            do_head(fp, nlines);
            fclose(fp);
        }
    }

    return 0;
}

static void do_head(FILE *fp, long long nlines) {
    int c;
    if (nlines <= 0) {
        return;
    }
    while ((c = fgetc(fp)) != EOF) {
        if (putchar(c) < 0) {
            exit(EXIT_FAILURE);
        }
        if (c == '\n' && --nlines <= 0) {
            return;
        }
    }
}
