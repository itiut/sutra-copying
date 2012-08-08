#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t) (int);

static sighandler_t trap_signal(int sig, sighandler_t handler);
static void trapped(int sig);

int main (int argc, char *argv[]) {
    trap_signal(SIGINT, trapped);
    while (1) {
        pause();
    }
    return 0;
}


static sighandler_t trap_signal(int sig, sighandler_t handler) {
    struct sigaction act, old;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    if (sigaction(sig, &act, &old) < 0) {
        return NULL;
    }

    return old.sa_handler;
}

static void trapped(int sig) {
    printf("signal trapped: %d\n", sig);
}
