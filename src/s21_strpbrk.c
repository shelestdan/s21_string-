#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    s21_size_t str = s21_strlen(str);
    s21_size_t sh = 0;
    int stat = 0;

    while(stat == 0 && sh < str) {
        sh++;
        if (s21_strchr(str2, str1[sh])) stat = 1;
    }
    return (char *)(stat ? (str1 + sh) : s21_NULL);
}