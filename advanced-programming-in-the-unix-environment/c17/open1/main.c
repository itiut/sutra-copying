/* Figure 17.18 */
#include "open.h"
#include <fcntl.h>

#define BUFFSIZE 8192

int main(int argc, char *argv[]) {
    int n, fd;
    char buf[BUFFSIZE];
    char line[MAXLINE];

    while (fgets(line, MAXLINE, stdin) != NULL) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        if ((fd = csopen(line, O_RDONLY)) == -1) {
            continue;
        }

        printf("read start\n");
        while ((n = read(fd, buf, BUFFSIZE)) > 0) {
            printf("read end\n");
            if (write(STDOUT_FILENO, buf, n) != n) {
                err_sys("write error");
            }
        }
        if (n == -1) {
            err_sys("read error");
        }
        close(fd);
    }
    return 0;
}
