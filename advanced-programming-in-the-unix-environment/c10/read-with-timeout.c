/* Figure 10.10 */
#include "apue.h"

static void sig_alrm(int);

int main() {
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        err_sys("signal(SIGALRM) error");
    }

    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
        err_sys("read error");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);
}

static void sig_alrm(int ingno) {
    /* nothing to do */
}
