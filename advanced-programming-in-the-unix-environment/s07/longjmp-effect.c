/* Figure 7.13 */
#include "apue.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2();

static jmp_buf jmpbuffer;
static int globval;

int main() {
    globval = 1;
    int          autoval = 2;
    register int regival = 3;
    volatile int volaval = 4;
    static int   statval = 5;

    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
               globval, autoval, regival, volaval, statval);
        return 0;
    }

    globval = 95;
    autoval = 96;
    regival = 97;
    volaval = 98;
    statval = 99;

    f1(autoval, regival, volaval, statval);
}

static void f1(int i, int j, int k, int l) {
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
           globval, i, j, k, l);
    f2();
}

static void f2() {
    longjmp(jmpbuffer, 1);
}
