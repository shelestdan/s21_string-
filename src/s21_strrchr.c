#include "s21_string.h"

char *s21_strrchr(const char *str, int ch) {
  const char *check = s21_NULL;
  if (str != s21_NULL) {
    while (*str++) {
      if (*str == (char)ch) {
        check = str;
      }
    } 
  }
  return (char *)check;
}