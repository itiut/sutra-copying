/* Figure C.7 */
#include "apue.h"
#include <time.h>

int main() {
    time_t t;
    struct tm *tm;
    char buf[MAXLINE];

    if ((t = time(NULL)) == -1) {
        err_sys("time error");
    }
    if ((tm = localtime(&t)) == NULL) {
        err_sys("localtime error");
    }
    if (strftime(buf, MAXLINE, "%a %b %d %T %Z %Y", tm) == 0) {
        err_sys("strftime error");
    }
    printf("%s\n", buf);
}
