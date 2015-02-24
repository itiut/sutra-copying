/* Exercise 15.15 */
#include "apue.h"
#include <sys/shm.h>

#define NLOOPS 1000

static int update(long *ptr) {
    return (*ptr)++;
}

int main() {
    int shmid, i, counter;
    pid_t pid;
    void *area;

    if ((shmid = shmget(IPC_PRIVATE, sizeof(long), 0600)) == -1) {
        err_sys("shmget error");
    }
    if ((area = shmat(shmid, 0, 0)) == (void *) -1) {
        err_sys("shmat erorr");
    }
    *(long *)area = 0;

    TELL_WAIT();

    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid > 0) {
        for (i = 0; i < NLOOPS; i+= 2) {
            if ((counter = update((long *) area)) != i) {
                err_quit("parent: expected %d, got %d", i, counter);
            }
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            err_sys("shmctl erorr");
        }
    } else {
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();
            if ((counter = update((long *) area)) != i) {
                err_quit("child: expected %d, got %d", i, counter);
            }
            TELL_PARENT(getppid());
        }
    }
}
