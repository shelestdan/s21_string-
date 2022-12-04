#include "s21_string.h"

// Разбивает строку str на ряд токенов, разделенных delim

char *s21_strtok(char *str, const char *delim) {
    if (str != s21_NULL) {
    for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
      for (s21_size_t j = 0; j <= s21_strlen(delim); j++) {
        if (str[i] == delim[j]) {
          str[i] = '\0';
        }
      }
    }
  }
  return str;
}