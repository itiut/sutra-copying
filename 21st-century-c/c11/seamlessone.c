// clang -fms-extensions -Wno-microsoft seamlessone.c
#include <math.h>
#include <stdio.h>

typedef struct point {
  double x, y;
} point;

typedef struct {
  point;
  double z;
} threepoint;

double threelength(threepoint p) {
  return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

int main(void) {
  threepoint p = {.x = 3, .y = 4, .z = 5};
  printf("p is %g units from the origin\n", threelength(p));
}
