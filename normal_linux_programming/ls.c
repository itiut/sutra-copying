#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

static void do_ls(const char *path);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        do_ls(argv[i]);
    }
    return 0;
}

static void do_ls(const char *path) {
    DIR *d = opendir(path);
    if (d == NULL) {
        perror(path);
        exit(EXIT_FAILURE);
    }

    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    closedir(d);
}
