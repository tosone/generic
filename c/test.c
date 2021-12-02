#include <stdint.h>
#include <stdio.h>

int cmpfunc(const void *a, const void *b) {
  return (*(signed int *)b > *(signed int *)a) ? 1 : 0;
}

int main(int argc, char const *argv[]) {
  int8_t a = 5;
  int8_t b = 5;
  printf("%d\n", cmpfunc(&a, &b));
  return 0;
}
