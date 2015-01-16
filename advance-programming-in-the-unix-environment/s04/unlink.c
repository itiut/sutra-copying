/* Figure 4.16 */
#include "apue.h"
#include <fcntl.h>

int main() {
    if (open("tempfile", O_RDWR) == -1) {
        err_sys("open error");
    }
    if (unlink("tempfile") == -1) {
        err_sys("unlink error");
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
}
