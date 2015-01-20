/* Figure C.1 */
#include "apue.h"
#include <limits.h>
#include <sys/resource.h>

#define OPEN_MAX_GUESS 256

long open_max() {
    long openmax;
    struct rlimit rl;

    if ((openmax = sysconf(_SC_OPEN_MAX)) == -1
        || openmax == LONG_MAX) {
        if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
            err_sys("cannot get file limit");
        }
        if (rl.rlim_max == RLIM_INFINITY) {
            openmax = OPEN_MAX_GUESS;
        } else {
            openmax = rl.rlim_max;
        }
    }
    return openmax;
}

int main() {
    printf("open_max = %ld\n", open_max());
}
