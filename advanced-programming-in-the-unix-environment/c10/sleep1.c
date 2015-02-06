/* Figure 10.7 */
#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo) {
    /* nothing to do */
}

unsigned int sleep1(unsigned int seconds) {
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        return seconds;
    }
    alarm(seconds);
    pause();
    return alarm(0);
}
