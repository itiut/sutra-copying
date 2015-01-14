#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    int fd1 = open(path, O_RDONLY);
    int fd2 = dup(fd1);
    int fd3 = open(path, O_RDONLY);

    int n;
    char buf[BUFFSIZE];
    if ((n = read(fd1, buf, BUFFSIZE)) < BUFFSIZE) {
        if (n == -1) {
            printf("read error\n");
            exit(EXIT_FAILURE);
        }
        printf("read EOF\n");
    }

    off_t offset;
    if ((offset = lseek(fd1, 0, SEEK_CUR)) == -1) {
        printf("lseek error for fd1\n");
        exit(EXIT_FAILURE);
    }
    printf("offset for df1 = %d\n", (int) offset);

    if ((offset = lseek(fd2, 0, SEEK_CUR)) == -1) {
        printf("lseek error for fd2\n");
        exit(EXIT_FAILURE);
    }
    printf("offset for fd2 = %d\n", (int) offset);

    if ((offset = lseek(fd3, 0, SEEK_CUR)) == -1) {
        printf("lseek error for fd3\n");
        exit(EXIT_FAILURE);
    }
    printf("offset for fd3 = %d\n", (int) offset);
    return 0;
}
