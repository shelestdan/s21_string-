// #include <string.h>
#include "s21_string.h"
#include <math.h>
#include <string.h>
#include <stdarg.h>

typedef struct info {
  va_list args;
  int width;
  int precision;
  int hex_size;
  int zero_padding;
  int point;
  int dash;
  int total_length;
  int sign;
  int is_zero;
  int space;
  int hash;
} s_info;

int main() {
  char kol[10000] = {0};
  s21_sprintf(kol, "%f %s %s %i", 3.32, "dasdasd", "popopopo", 8);
  // sprintf(kol, "%s %f %s %i", "dasdasd", 3.32, "popopopo", 8);
  printf("%s", kol);

  return 0;
}

