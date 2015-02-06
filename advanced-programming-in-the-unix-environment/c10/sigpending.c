/* Figure 10.15 */
#include "apue.h"

static void sig_quit(int);

int main() {
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        err_sys("cannot catch SIGQUIT");
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
        err_sys("SIG_BLOCK error");
    }

    sleep(5);

    if (sigpending(&pendmask) == -1) {
        err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nSIGQUIT pending\n");
    }

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked\n");

    sleep(5);
}

static void sig_quit(int signo) {
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        err_sys("cannot reset SIGQUIT");
    }
}
