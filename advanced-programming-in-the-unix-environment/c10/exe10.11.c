/* Exercise 10.11 */
#include "apue.h"
#include <signal.h>
#include <sys/resource.h>

#define BUFFSIZE 100

void sig_xfsz(int signo) {
    printf("SIGXFSZ caught\n");
}

int main() {
    int n;
    char buf[BUFFSIZE];

    signal_intr(SIGXFSZ, sig_xfsz);

    struct rlimit rlimit;
    if (getrlimit(RLIMIT_FSIZE, &rlimit) == -1) {
        err_sys("getrlimit error");
    }
    rlimit.rlim_cur = 1024;
    if (setrlimit(RLIMIT_FSIZE, &rlimit) == -1) {
        err_sys("setrlimit error");
    }

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        int wrote;
        if ((wrote = write(STDOUT_FILENO, buf, n)) == -1) {
            err_sys("write error");
        } else if (wrote < n) {
            printf("Wrote %d\n", wrote);
        }
    }
    if (n < 0) {
        err_sys("read error");
    }
}
