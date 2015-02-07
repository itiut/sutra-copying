/* Figure 11.2 */
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid, (unsigned long) tid, (unsigned long) tid);
}

void *thr_fn(void *arg) {
    printids("new thread: ");
    return (void *) 0;
}

int main() {
    int err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        err_exit(err, "can't create thread");
    }
    printids("main thread:");
    sleep(1);
}
