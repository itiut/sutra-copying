#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

static int open_connection(char *host, char* service);

int main (int argc, char *argv[]) {
    char *host = (argc > 1) ? argv[1] : "localhost";
    int sock = open_connection(host, "daytime");
    FILE *fp = fdopen(sock, "r");
    if (fp == NULL) {
        perror("fdopen(3)");
        exit(EXIT_FAILURE);
    }

    char buf[BUFSIZ];
    fgets(buf, sizeof(buf), fp);
    fclose(fp);
    fputs(buf, stdout);

    return 0;
}

static int open_connection(char *host, char *service) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *res;
    int err;
    if ((err = getaddrinfo(host, service, &hints, &res)) < 0) {
        fprintf(stderr, "getaddrinfo(3): %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    for (struct addrinfo *ai = res; ai;ai = ai->ai_next) {
        int sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sock < 0) {
            continue;
        }
        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            close(sock);
            continue;
        }
        freeaddrinfo(res);
        return sock;
    }
    fprintf(stderr, "socket(2)/connect(2) failed\n");
    freeaddrinfo(res);
    exit(EXIT_FAILURE);
}
