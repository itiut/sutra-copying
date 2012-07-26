#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <stdbool.h>
#include <unistd.h>

static void do_grep(regex_t *pat, FILE *src);

static bool bIgnoreCase = false;
static bool bInvertMatch = false;

int main (int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "iv")) != -1) {
        switch (opt) {
        case 'i':
            bIgnoreCase = true;
            break;
        case 'v':
            bInvertMatch = true;
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-i] [-v] <pattern> [FILE ...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (argc == optind) {
        fprintf(stderr, "Usage: %s [-i] [-v] <pattern> [FILE ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    argc -= optind;
    argv += optind;

    regex_t pat;
    int flag = REG_EXTENDED | REG_NOSUB | REG_NEWLINE;
    if (bIgnoreCase) {
        flag |= REG_ICASE;
    }
    int err = regcomp(&pat, argv[0], flag);
    if (err != 0) {
        char buf[1024];

        regerror(err, &pat, buf, sizeof(buf));
        fprintf(stderr, "%s\n", buf);
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        do_grep(&pat, stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                exit(EXIT_FAILURE);
            }
            do_grep(&pat, fp);
            fclose(fp);
        }
    }
    regfree(&pat);
    return 0;
}

static void do_grep(regex_t *pat, FILE *src) {
    char buf[4096];

    while (fgets(buf, sizeof(buf), src) != NULL) {
        if ((regexec(pat, buf, 0, NULL, 0) == 0) ^ bInvertMatch) {
            fputs(buf, stdout);
        }
    }
}
