/* Figure 8.24 */
#include "apue.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        err_quit("command-line argument required");
    }

    int status;
    if ((status = system(argv[1])) < 0) {
        err_sys("system() error");
    }
    pr_exit(status);

    return 0;
}
