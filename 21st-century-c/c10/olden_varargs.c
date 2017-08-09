#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int system_w_printf(char const *fmt, ...) \
    __attribute__((format(printf, 1, 2)));

int system_w_printf(char const *fmt, ...) {
    char *cmd;
    va_list argp;
    va_start(argp, fmt);
    vasprintf(&cmd, fmt, argp);
    va_end(argp);
    int out = system(cmd);
    free(cmd);
    return out;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    return system_w_printf("ls %s", argv[1]);
}
