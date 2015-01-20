/* Figure 4.24 */
#include "apue.h"

int main() {
    if (chdir("/tmp") == -1) {
        err_sys("chdir failed");
    }

    size_t size;
    char *ptr = path_alloc(&size);
    if (getcwd(ptr, size) == NULL) {
        err_sys("getcwd failed");
    }

    printf("cwd = %s\n", ptr);
}
