#include "s21_string.h"

int s21_strncmp(const char *str_1, const char *str_2, s21_size_t n) {
   s21_size_t x = 0;
  for (x = 0; x < (n - 1); x++) {
   if (str_1[x] != str_2[x]) {
    break;
    } 
} return str_1[x] - str_2[x];
}
