#include "s21_sprintf.h"

#include "s21_string.h"

s_info *initialise(s_info *ints) {
  ints->width = 0;
  ints->precision = 0;
  ints->hex_size = 0;
  ints->zero_padding = 0;
  ints->point = 0;
  ints->dash = 0;
  ints->total_length = 0;
  ints->sign = 0;
  ints->is_zero = 0;
  ints->space = 0;
  ints->hash = 0;
  return (ints);
}

void reverse(char *str, int len) {
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

int intToStr(int x, char str[], int d) {
  int i = 0;
  while (x) {
    str[i++] = (x % 10) + '0';
    x = x / 10;
  }
  while (i < d) str[i++] = '0';
  reverse(str, i);
  str[i] = '\0';
  return i;
}

void ftoa(float n, char *res, int afterpoint) {
  int ipart = (int)n;
  float fpart = n - (float)ipart;
  int i = intToStr(ipart, res, 0);
  if (afterpoint != 0) {
    res[i] = '.';
    fpart = fpart * pow(10, afterpoint);
    fpart = fpart * 10.0f;
    fpart = fpart > 0 ? floor(fpart+0.5f) : ceil(fpart-0.5f);
    fpart = fpart / 10.0f;
    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list agr;
  va_start(agr, *format);
  char pattern_f_d[9000] = {0};
  while (*format != '\0') {
    if (*format == ' ') {
      format++;
      strcat(str, " ");
      continue;
    }
    if (*format == '%') {
      format++;
      if (*format == '%') {
        format++;
        strcat(str, "%");
        continue;
      }
      if (*format == 's') {
        format++;
        char *pattern = va_arg(agr, char *);
        strcat(str, pattern);
        continue;
      }
      if (*format == 'f') {
        format++;
        double pattern = va_arg(agr, double);
        ftoa(pattern, pattern_f_d, 6);
        strcat(str, pattern_f_d);
        continue;
      }
      if (*format == 'd' || *format == 'i') {
        format++;
        int pattern = va_arg(agr, int);
        // printf("%d", pattern);
        intToStr(pattern, pattern_f_d, 1);
        strcat(str, pattern_f_d);
        continue;
      }
    } else {
      // str = strcat(str, format);
    }
    format++;
  }
  va_end(agr);
  return 0;
}