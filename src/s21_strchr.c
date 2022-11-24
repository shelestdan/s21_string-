#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *temp;
  temp = (char *)str;
  while (*temp != '\0') {
    if (*temp == (char)c) {
      temp++;
    }
    temp++;
  }
  if (*temp == (char)c) {
    return (temp);
  }
  return (s21_NULL);
}
