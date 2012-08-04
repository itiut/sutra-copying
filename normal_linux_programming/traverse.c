#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

static void do_traverse(const char *path);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "%s: no arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        do_traverse(argv[i]);
    }
    return 0;
}

static void do_traverse(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        exit(EXIT_FAILURE);
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(".", ent->d_name) != 0 && strcmp("..", ent->d_name) != 0) {
            printf("%s/%s\n", path, ent->d_name);
            if (ent->d_type == DT_DIR) {
                char *subdir = (char *) calloc(strlen(path) + strlen(ent->d_name) + 2, sizeof(char));
                strcat(subdir, path);
                strcat(subdir, "/");
                strcat(subdir, ent->d_name);
                do_traverse(subdir);
                free(subdir);
            }
        }
    }
}
