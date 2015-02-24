/* Exercise 15.10, Figure C.20 */
#include "apue.h"
#include <fcntl.h>

#define FIFO "temp.fifo"

int main() {
    int fdread, fdwrite;

    unlink(FIFO);
    if (mkfifo(FIFO, FILE_MODE) == -1) {
        err_sys("mkfifo errro");
    }
    if ((fdread = open(FIFO, O_RDONLY | O_NONBLOCK)) == -1) {
        err_sys("open error for reading");
    }
    if ((fdwrite = open(FIFO, O_WRONLY)) == -1) {
        err_sys("open error for writing");
    }
    clr_fl(fdread, O_NONBLOCK);
}
