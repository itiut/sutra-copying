/* Figure 10.8, 10.9 */
#include "apue.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo) {
    longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int seconds) {
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        return seconds;
    }
    if (setjmp(env_alrm) == 0) {
        alarm(seconds);
        pause();
    }
    return alarm(0);
}

static void sig_int(int);

int main() {
    unsigned int unslept;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        err_sys("signal(SIGINT) error");
    }
    unslept = sleep(5);
    printf("sleep2 returned: %u\n", unslept);
}

static void sig_int(int signo) {
    volatile int k;

    printf("\nsig_int starting\n");
    for (int i = 0; i < 300000; i++) {
        for (int j = 0; j < 30000; j++) {
            k += i * j;
        }
    }
    printf("sig_int finished\n");
}
