/* Figure 13.9 */
#include "apue.h"
#include <fcntl.h>

int set_cloexec(int fd) {
    int val;

    if ((val = fcntl(fd, F_GETFD, 0)) == -1) {
        return -1;
    }
    val |= FD_CLOEXEC;
    return fcntl(fd, F_SETFD, val);
}
