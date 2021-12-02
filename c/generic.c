#include <math.h>
#include <stdio.h>
#include <tgmath.h>

// ------------------------自定义泛型扩展----------------------------
#define my_cbrt(X) \
  _Generic((X), long double : cbrtl, default : cbrt, float : cbrtf)(X)

void test() {
  double x = 8.0;
  const float y = 3.375;
  printf("cbrt(8.0) = %f\n", my_cbrt(x));
  printf("cbrtf(3.375) = %f\n", my_cbrt(y));
}

int main(void) {
  test();
  return 0;
}
