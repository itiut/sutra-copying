/* Figure 16.16 */
#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128

extern int connect_retry(int, int, int, const struct sockaddr*, socklen_t);

void print_uptime(int sockfd) {
    int n;
    char buf[BUFLEN];

    while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    if (n == -1) {
        err_sys("recv error");
    }
}

int main(int argc, char *argv[]) {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if (argc != 2) {
        err_quit("usage: %s hostname", argv[0]);
    }
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0) {
        err_quit("getaaddrinfo error: %s", gai_strerror(err));
    }
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, aip->ai_addr, aip->ai_addrlen)) == -1) {
            err = errno;
        } else {
            print_uptime(sockfd);
            return 0;
        }
    }
    err_exit(err, "can't conect to %s", argv[1]);
}
