// clang dict_use.c dict.c keyval.c
#include <stdio.h>
#include "dict.h"

int main() {
    int zero = 0;
    double one = 1.0;
    char two[] = "two";
    dictionary_s *d = dictionary_new();
    dictionary_add(d, "an int", &zero);
    dictionary_add(d, "a double", &one);
    dictionary_add(d, "a string", &two);
    printf("The integer I Recorded was: %i\n", *(int *)dictionary_find(d, "a integer"));
    printf("The string was: %s\n", (char *)dictionary_find(d, "a string"));
    dictionary_free(d);
}
