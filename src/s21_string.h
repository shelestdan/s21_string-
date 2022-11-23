#include <stdio.h>

typedef long unsigned s21_size_t;
#define s21_NULL (void*)0

s21_size_t s21_strlen(const char *str); // Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strcspn(const char *str1, const char *str2); // Вычисляет длину начального сегмента str1, который полностью состоит из символов, не входящих в str2.
s21_size_t s21_strspn(const char *str1, const char *str2); // Вычисляет длину начального сегмента str1, который полностью состоит из символов str2.

char *s21_strpbrk(const char *str1, const char *str2); //Функция выполняет поиск первого вхождения в строку str1 любого из символов строки str2
char *s21_strchr(const char *str, int c); //возвращает указатель на первое вхождение младшего байта параметра ch в строку str
void *s21_memchr(const void *str, int c, s21_size_t n); //поиск первого вхождения указанного символа в массиве.
char *s21_strcat(char *dest, const char *src); // объединение строк
char *s21_strncat(char *dest, const char *src, s21_size_t n); //  объединение строк c ограничением длины добавляемой строки
