#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *temp;
  char *buf;
  temp = (char *)str;
  buf = NULL;
  while (*temp != '\0') {
    if (*temp == (char)c) {
      buf = temp;
    }
    temp++;
  }
  if (*temp == (char)c) {
    buf = temp;
  }
  return (buf);
}
