/* Figure 3.12 */
#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags) {
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) == -1) {
        err_sys("fcntl F_GETFL error");
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) == -1) {
        err_sys("fcntl F_SETFL error");
    }
}
