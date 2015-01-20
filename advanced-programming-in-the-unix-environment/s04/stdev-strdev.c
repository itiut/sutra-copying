/* Figure 4.25 */
#include "apue.h"
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);

        struct stat buf;
        if (stat(argv[i], &buf) == -1) {
            err_ret("stat error");
            continue;
        }

        /* Does not work in OS X clang */
        /* Works in gcc 4.9.1 with -std=gnu99 */
        printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
            printf(" (%s) rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_rdev), minor(buf.st_rdev));
        }
        printf("\n");
    }
    return 0;
}
