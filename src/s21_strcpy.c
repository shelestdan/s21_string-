#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
//   int i = 0;
//   s21_size_t len = s21_strlen(src);
//   while (src[i] != '\0') {
//     for (s21_size_t i = 0; i < len; i++) {
//       dest[i] = src[i];
//     }
//   }
//   // dest[i] = '\0';
//   return dest;
// }
  int srcptrLength = s21_strlen(src);

  for (int x = 0; x <= srcptrLength; x += 1) {
    dest[x] = src[x];
  }

  return dest;
}