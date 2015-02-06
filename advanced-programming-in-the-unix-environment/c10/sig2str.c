/* Exercise 10.2 */
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int sig2str(int signo, char *str) {
    if (str == NULL) {
        return -1;
    }

    char *namep;
    if ((namep = strsignal(signo)) == NULL) {
        return -1;
    }
    strcpy(str, namep);
    free(namep);
    return 0;
}
