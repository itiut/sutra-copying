#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        do_cat(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            do_cat(argv[i]);
        }
    }
    return 0;
}

#define BUFFER_SIZE 2048

static void do_cat(const char *path) {
    int fd = (path == NULL) ? STDIN_FILENO : open(path, O_RDONLY);
    if (fd < 0) {
        die(path);
    }

    while (1) {
        unsigned char buf[BUFFER_SIZE];
        int n = read(fd, buf, sizeof(buf));

        if (n < 0) {
            die(path);
        } else if (n == 0) {
            break;
        }
        if (write(STDOUT_FILENO, buf, n) < 0) {
            die(path);
        }
    }
}

static void die(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
