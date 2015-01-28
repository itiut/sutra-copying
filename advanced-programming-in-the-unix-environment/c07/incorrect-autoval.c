/* Figure 7.14 */
#include <stdio.h>

FILE *open_data() {
    FILE *fp;
    char databuf[BUFSIZ];

    if ((fp = fopen("datafile", "r")) == NULL) {
        return NULL;
    }
    if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) == -1) {
        return NULL;
    }
    return fp;
}
