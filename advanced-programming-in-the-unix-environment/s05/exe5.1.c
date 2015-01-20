#include "apue.h"
#include <stdio.h>

void setbuf(FILE *restrict fp, char *restrict buf) {
    if (setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ)) {
        /* error */
        err_sys("setbuf error");
    }
}
