#include "apue.h"
#include <unistd.h>

static void pr_ids(char *name) {
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, sid = %ld, tpgrp = %ld\n",
           name, (long) getpid(), (long) getppid(), (long) getpgrp(), (long) getsid(0), (long) tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main() {
    pid_t pid;

    pr_ids("parent");

    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* child */
        if (setsid() == -1) {
            err_sys("setsid error");
        }
        pr_ids("child");
        exit(0);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        err_sys("waitpid erorr");
    }
}
