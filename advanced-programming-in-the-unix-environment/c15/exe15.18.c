/* Exercise 15.18 */
#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(sem_t *sem) {
    int val;
    if (sem_getvalue(sem, &val) == -1) {
        err_sys("sem_getvalue erorr");
    }
    sem_post(sem);
    return val;
}

int main() {
    int i, counter;
    pid_t pid;
    sem_t *sem[3];
    char name[MAXLINE];

    for (i = 0; i < 3; i++) {
        snprintf(name, sizeof(name), "/%ld.%d", (long) getpid(), i);
        if ((sem[i] = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, 0)) == SEM_FAILED) {
            err_sys("sem_open erorr");
        }
    }

    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid > 0) {
        for (i = 0; i < NLOOPS; i+= 2) {
            if ((counter = update(sem[0])) != i) {
                err_quit("parent: expected %d, got %d", i, counter);
            }
            printf("p: %d\n", counter);
            sem_post(sem[1]);
            sem_wait(sem[2]);
        }

        for (i = 0; i < 3; i++) {
            sem_close(sem[i]);
        }
    } else {
        for (i = 1; i < NLOOPS + 1; i += 2) {
            sem_wait(sem[1]);
            if ((counter = update(sem[0])) != i) {
                err_quit("child: expected %d, got %d", i, counter);
            }
            printf("c: %d\n", counter);
            sem_post(sem[2]);
        }
    }
}
