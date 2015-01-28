/* Figure 4.12 */
#include "apue.h"

int main() {
    struct stat statbuf;

    if (stat("foo", &statbuf) == -1) {
        err_sys("stat error for foo");
    }
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) == -1) {
        err_sys("chmod error for foo");
    }

    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        err_sys("chmod error for bar");
    }
}
