#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int main() {
    char good_template[] = "/tmp/dirXXXXXX";
    char *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
}

void make_temp(char *template) {
    int fd;
    if ((fd = mkstemp(template)) == -1) {
        err_sys("cannot create temp file");
    }
    printf("temp name = %s\n", template);
    close(fd);

    struct stat sbuf;
    if (stat(template, &sbuf) == -1) {
        if (errno == ENOENT) {
            printf("file doesn't exist\n");
        } else {
            err_sys("stat failed");
        }
    } else {
        printf("file exists\n");
        unlink(template);
    }
}
