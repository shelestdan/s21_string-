#include "s21_string.h"

char *s21_strncpy (char *dest, const char *src, s21_size_t n) {
    s21_size_t len = s21_strlen(src);
    s21_size_t i = 0;
    int count = 0;
    if (len < n) {
         while(dest[i] != '\0') {
            dest[i] = src[i];
            count++;
            i++;
        }
        for(s21_size_t i = 0; i <= (n - len); i++) {
            dest[count - 1] = '\0';
            count++;
        }
    } else {
        while(i < n) {
            dest[i] = src[i];
            i++;
        }
    }
    return dest;
}