/* Figure 8.3 */
#include "apue.h"

int globvar = 6;

int main() {
    int var = 88;
    printf("before vfork\n");

    pid_t pid;
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        globvar++;
        var++;
        _exit(0);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
}
