/* Figure 4.21 */
#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        struct stat statbuf;
        if (stat(argv[i], &statbuf) == -1) {
            err_ret("%s: stat error", argv[i]);
            continue;
        }

        int fd;
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) == -1) {
            err_ret("%s: open error", argv[i]);
            continue;
        }

        /* Does not work in OS X clang */
        /* Works in gcc 4.9.1 with -std=gnu99 */
        struct timespec times[2];
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
        if (futimens(fd, times) == -1) {
            err_ret("%s: futimens error", argv[i]);
        }
        close(fd);
    }
    return 0;
}
