/* Figure 17.29 */
#include "opend.h"
#include <sys/select.h>

void loop() {
    int i, n, maxfd, maxi, listenfd, clifd, nread;
    char buf[MAXLINE];
    uid_t uid;
    fd_set rset, allset;

    FD_ZERO(&allset);

    if ((listenfd = serv_listen(CS_OPEN)) == -1) {
        log_sys("serv_listen error");
    }
    FD_SET(listenfd, &allset);
    maxfd = listenfd;
    maxi = -1;

    for (;;) {
        rset = allset;
        if ((n = select(maxfd + 1, &rset, NULL, NULL, NULL)) == -1) {
            log_sys("select error");
        }

        if (FD_ISSET(listenfd, &rset)) {
            if ((clifd = serv_accept(listenfd, &uid)) == -1) {
                log_sys("serv_accept eror: %d", clifd);
            }
            i = client_add(clifd, uid);
            FD_SET(clifd, &allset);
            if (clifd > maxfd) {
                maxfd = clifd;
            }
            if (i > maxi) {
                maxi = i;
            }
            log_msg("new connection: uid %d, fd %d", uid, clifd);
            continue;
        }

        for (i = 0; i <= maxi; i++) {
            if ((clifd = client[i].fd) == -1) {
                continue;
            }
            if (FD_ISSET(clifd, &rset)) {
                if ((nread = read(clifd, buf, MAXLINE)) == -1) {
                    log_sys("read error on fd %d", clifd);
                } else if (nread == 0) {
                    log_msg("closed: uid %d, fd %d", client[i].uid, clifd);
                    client_del(clifd);
                    FD_CLR(clifd, &allset);
                    close(clifd);
                } else {
                    handle_request(buf, nread, clifd, client[i].uid);
                }
            }
        }
    }
}