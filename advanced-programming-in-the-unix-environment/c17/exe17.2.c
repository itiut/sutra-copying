/* Exercise 17.2 */
#include "apue.h"
#include <fcntl.h>

#define FILENAME "temp.out"

int main() {
    int fd[2];
    if ((fd[0] = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        err_sys("open error");
    }
    if (write(fd[0], "abcde", 5) != 5) {
        err_sys("write error");
    }
    close(fd[0]);

    if (fd_pipe(fd) == -1) {
        err_sys("fd_pipe error");
    }

    TELL_WAIT();
    pid_t pid;
    int sfd;
    if ((pid = fork()) == -1) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* child */
        close(fd[0]);

        if ((sfd = open(FILENAME, O_RDONLY)) == -1) {
            err_sys("open error");
        }
        send_fd(fd[1], sfd);
        lseek(sfd, 3, SEEK_SET);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lseek(sfd, 1, SEEK_SET);
        TELL_PARENT(getppid());
    } else {
        /* parent */
        close(fd[1]);

        if ((sfd = recv_fd(fd[0], write)) < 0) {
            err_sys("recv_fd error");
        }
        WAIT_CHILD();
        char c;
        if (read(sfd, &c, 1) != 1) {
            err_sys("read error");
        }
        printf("%c\n", c);      /* d */
        TELL_CHILD(pid);
        WAIT_CHILD();
        if (read(sfd, &c, 1) != 1) {
            err_sys("read error");
        }
        printf("%c\n", c);      /* b */
        waitpid(pid, NULL, 0);
    }
}
