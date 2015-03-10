#ifndef OPEND1_H
#define OPEND1_H

/* Figure 17.20 */
#include "apue.h"
#include <errno.h>

#define CL_OPEN "open"

extern char errmsg[];
extern int oflag;
extern char *pathname;

int cli_args(int, char **);
void handle_request(char *, int, int);

#endif /* OPEND1_H */
