/* Figure 17.21 */
#include "opend.h"

char errmsg[MAXLINE];
int oflag;
char *pathname;

int main() {
    int nread;
    char buf[MAXLINE];

    for (;;) {
        if ((nread = read(STDIN_FILENO, buf, MAXLINE)) == -1) {
            err_sys("read errro on stream pipe");
        } else if (nread == 0) {
            break;
        }
        handle_request(buf, nread, STDOUT_FILENO);
    }
}
