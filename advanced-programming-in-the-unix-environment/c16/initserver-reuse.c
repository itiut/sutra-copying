/* Figure 16.22 */
#include "apue.h"
#include <errno.h>
#include <sys/socket.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen) {
    int fd, err;
    int reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) == -1) {
        return -1;
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        goto errout;
    }
    if (bind(fd, addr, alen) == -1) {
        goto errout;
    }
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(fd, qlen) == -1) {
            goto errout;
        }
    }
    return fd;

errout:
    err = errno;
    close(fd);
    errno = err;
    return -1;
}
