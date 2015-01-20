/* Figure 4.23 */
#include "apue.h"

int main() {
    if (chdir("/tmp") == -1) {
        err_sys("chdir failed");
    }
    printf("chdir to /tmp succeeded\n");
}
