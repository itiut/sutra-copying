/* Exercise 10.9 */
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include "apue.h"

extern const char * const sys_signame[];

void pr_mask(const char *str) {
    sigset_t sigset;
    int  errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) == -1) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", str);
        for (unsigned int i = 0; i < sizeof(sys_signame); i++) {
            if (sys_signame[i] == NULL || sys_signame[i][0] == '\0') {
                break;
            }
            if (strcmp(sys_signame[i], "Signal 0") == 0) {
                continue;
            }

            if (sigismember(&sigset, i)) {
                printf(" SIG");
                for (const char *p = sys_signame[i]; *p != '\0'; p++) {
                    putchar(toupper(*p));
                }
            }
        }
        printf("\n");
    }

    errno = errno_save;
}

int main() {
    sigset_t sigset;
    sigfillset(&sigset);
    if (sigprocmask(SIG_SETMASK, &sigset, NULL) == -1) {
        err_sys("sigprocmask error");
    }
    pr_mask("fillset");

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGQUIT);
    if (sigprocmask(SIG_SETMASK, &sigset, NULL) == -1) {
        err_sys("sigprocmask error");
    }
    pr_mask("intquit");
}
