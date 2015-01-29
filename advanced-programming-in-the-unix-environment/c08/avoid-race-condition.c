/* Figure 8.13 */
#include "apue.h"

static void charatatime(char *);

int main() {
    pid_t pid;

    TELL_WAIT();

    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid == 0) {
        WAIT_PARENT();
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
    }
}

static void charatatime(char *str) {
    setbuf(stdout, NULL);
    for (char *ptr = str; *ptr != '\0'; ptr++) {
        putc(*ptr, stdout);
    }
}
