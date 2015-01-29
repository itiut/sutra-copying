/* Figure 8.25 */
#include "apue.h"

int main() {
    printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
}
