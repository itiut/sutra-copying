/* Figure 17.24 */
#include "opend.h"

int cli_args(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0) {
        snprintf(errmsg, MAXLINE-1, "usage: <pathname> <oflag>: %s %s %s (%d)\n", argv[0], argv[1], argv[2], argc);
        strcpy(errmsg, "usage: <pathname> <oflag>\n");
        return -1;
    }
    pathname = argv[1];
    oflag = atoi(argv[2]);
    return 0;
}
