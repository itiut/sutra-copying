/* Figure 4.3 */
#include "apue.h"

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);

        struct stat buf;
        if (lstat(argv[i], &buf) == -1) {
            err_ret("lstat error");
            continue;
        }

        char *ptr;
        if (S_ISREG(buf.st_mode)) {
            ptr = "regular";
        } else if (S_ISDIR(buf.st_mode)) {
            ptr = "directory";
        } else if (S_ISCHR(buf.st_mode)) {
            ptr = "character special";
        } else if (S_ISBLK(buf.st_mode)) {
            ptr = "block special";
        } else if (S_ISFIFO(buf.st_mode)) {
            ptr = "fifo";
        } else if (S_ISLNK(buf.st_mode)) {
            ptr = "symblock link";
        } else if (S_ISSOCK(buf.st_mode)) {
            ptr = "socket";
        } else {
            ptr = "** unknown mode **";
        }
        printf("%s\n", ptr);
    }
    return 0;
}
