/* Figure 7.9 */
#include "apue.h"

#define TOK_ADD 5

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main() {
    char line[MAXLINE];

    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }
}

char *tok_ptr;

void do_line(char *ptr) {
    int cmd;

    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch (cmd) {
        case TOK_ADD:
            cmd_add();
            break;
        }
    }
}

void cmd_add() {
    int token = get_token();
    /* rest of processing for this command */
}

int get_token() {
    /* fetch next token from line pointed to by tok_ptr */
}
