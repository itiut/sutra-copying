/* Figure 7.11 */
#include "apue.h"
#include <setjmp.h>

#define TOK_ADD 5

void do_line(char *);
void cmd_add(void);
int get_token(void);

jmp_buf jmpbuffer;

int main() {
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0) {
        printf("error");
    }
    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }
}

void cmd_add() {
    int token = get_token();

    if (token < 0) {
        longjmp(jmpbuffer, 1);
    }
}
