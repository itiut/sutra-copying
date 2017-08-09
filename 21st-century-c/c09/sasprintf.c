#include <stdio.h>
#include <stdlib.h>

#define Sasprintf(write_to, ...) {            \
    char *tmp_string_for_extend = (write_to); \
    asprintf(&(write_to), __VA_ARGS__);       \
    free(tmp_string_for_extend);              \
}

int main() {
    int i = 3;
    char *q = NULL;
    Sasprintf(q, "SELECT * FROM tab");
    Sasprintf(q, "%s WHERE col%i IS NOT NULL", q, i);
    printf("%s\n", q);
}
