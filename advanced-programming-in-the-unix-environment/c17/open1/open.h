#ifndef OPEN_H
#define OPEN_H

/* Figure 17.17 */
#include "apue.h"
#include <errno.h>

#define CS_OPEN "/tmp/opend.socket"
#define CL_OPEN "open"

int csopen(char *, int);

#endif /* OPEN_H */
