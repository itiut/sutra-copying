/* Figure 10.5 */
#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        err_sys("getpwnam(root) error");
    }
    alarm(1);
}

int main() {
    char *name;
    if ((name = getlogin()) == NULL) {
        err_sys("getlogin error");
    }

    signal(SIGALRM, my_alarm);
    alarm(1);
    for (;;) {
        struct passwd *ptr;
        if ((ptr = getpwnam(name)) == NULL) {
            err_sys("getpwnam error");
        }
        if (strcmp(ptr->pw_name, name) != 0) {
            printf("return value corrupted!, pw_name  %s\n", ptr->pw_name);
        }
    }
}
