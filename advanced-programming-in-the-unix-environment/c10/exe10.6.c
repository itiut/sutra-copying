/* Exercise 10.6 */
#include "apue.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

void increment(int fd, const char *pname) {
    int val;
    lseek(fd, SEEK_SET, 0);
    if (read(fd, &val, sizeof(val)) != sizeof(val)) {
        err_sys("read error");
    }

    val++;
    lseek(fd, SEEK_SET, 0);
    if (write(fd, &val, sizeof(val)) != sizeof(val)) {
        err_sys("write error");
    }

    printf("%6s: increment -> %d\n", pname, val);
}

int main() {
    int fd;
    if ((fd = open("foo.temp", O_RDWR | O_CREAT | O_TRUNC)) == -1) {
        err_sys("open error");
    }

    int val = 0;
    if (write(fd, &val, sizeof(val)) != sizeof(val)) {
        err_sys("write error");
    }
    printf("initial value = %d\n", val);

    TELL_WAIT();

    pid_t pid;
    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* child */
        for (int i = 0; i < 10; i++) {
            WAIT_PARENT();
            increment(fd, "child");
            TELL_PARENT(getppid());
        }
        exit(0);
    }

    /* parent */
    for (int i = 0; i < 10; i++) {
        increment(fd, "parent");
        TELL_CHILD(pid);
        WAIT_CHILD();
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        err_sys("waitpid error");
    }
}
