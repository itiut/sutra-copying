/* Figure 17.31 */
#include "opend.h"
#include <fcntl.h>

void handle_request(char *buf, int nread, int clifd, uid_t uid) {
    int newfd;

    if (buf[nread-1] != '\0') {
        snprintf(errmsg, MAXLINE-1, "request from uid %d not null terminated: %*.*s\n", uid, nread, nread, buf);
        send_err(clifd, -1, errmsg);
        return;
    }
    log_msg("request: %d, from uid %d", buf, uid);

    if (buf_args(buf, cli_args) == -1) {
        send_err(clifd, -1, errmsg);
        log_msg(errmsg);
        return;
    }
    if ((newfd = open(pathname, oflag)) == -1) {
        snprintf(errmsg, MAXLINE-1, "cant open %s: %s\n", pathname, strerror(errno));
        send_err(clifd, -1, errmsg);
        log_msg(errmsg);
        return;
    }
    if (send_fd(clifd, newfd) == -1) {
        log_sys("send_fd error");
    }
    log_msg("send fd %d over fd %d for %s", newfd, clifd, pathname);
    close(newfd);
}
