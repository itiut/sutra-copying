#include <stdio.h>
#include <string.h>

int count_lines(char *instring) {
    int counter = 0;
    char *scratch, *txt, *delimiter = "\n";
    while ((txt = strtok_r(!counter ? instring : NULL, delimiter, &scratch))) {
        counter++;
    }
    return counter;
}

int main() {
    char *str = strdup("\
aiueo\n\
kakikukeko\n\
sashisuseso");
    printf("%i\n", count_lines(str));
}
