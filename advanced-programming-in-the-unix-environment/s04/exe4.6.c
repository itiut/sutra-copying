/* Exercise 4.6 */
#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        err_quit("usage: %s SOURCE DEST", argv[0]);
    }

    int srcfd, dstfd;
    if ((srcfd = open(argv[1], O_RDONLY)) == -1) {
        err_quit("open error for reading %s", argv[1]);
    }
    if ((dstfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE)) == -1) {
        err_quit("open error for writing %s", argv[2]);
    }

    char buf[BUFSIZ];
    ssize_t n;
    while ((n = read(srcfd, buf, BUFSIZ)) > 0) {
        for (int i = 0; i < n; i++) {
            if (buf[i] == 0) {
                /* hole */
                if (lseek(dstfd, 1, SEEK_CUR) == -1) {
                    err_quit("lseek error for %s", argv[2]);
                }
                continue;
            }
            if (write(dstfd, buf + i, 1) == -1) {
                err_quit("write error for %s", argv[2]);
            }
        }
    }
    if (n == -1) {
        err_sys("read error for %s", argv[1]);
    }
    return 0;
}
