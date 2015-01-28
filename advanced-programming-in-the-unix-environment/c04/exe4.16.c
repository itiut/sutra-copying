/* Figure C.3 */
#include "apue.h"
#include <fcntl.h>

#define DEPTH 1000
#define STARTDIR "/tmp"
#define NAME "alonglonglonglonglonglonglonglonglonglongname"
#define MAXSZ (10*8192)

int main() {
    if (chdir(STARTDIR) == -1) {
        err_sys("chdir error");
    }

    for (int i = 0; i < DEPTH; i++) {
        if (mkdir(NAME, DIR_MODE) == -1) {
            err_sys("mkdir failed, i = %d\n", i);
        }
        if (chdir(NAME) == -1) {
            err_sys("chdir failed, i = %d\n", i);
        }
    }

    if (creat("afile", FILE_MODE) == -1) {
        err_sys("creat error");
    }

    size_t size;
    char *path;
    path = path_alloc(&size);
    while (1) {
        if (getcwd(path, size) != NULL) {
            break;
        } else {
            err_ret("getcwd failed, size = %ld", (long) size);
            size += 100;
            if (size > MAXSZ) {
                err_quit("giving up");
            }
            if ((path = realloc(path, size)) == NULL) {
                err_sys("realloc error");
            }
        }
    }
    printf("length = %ld\n%s\n", (long) strlen(path), path);
}
