#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <unistd.h>


typedef long unsigned s21_size_t;
#define s21_NULL (void*)0

s21_size_t s21_strlen(const char *str); // Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strcspn(const char *str1, const char *str2); // Вычисляет длину начального сегмента str1, который полностью состоит из символов, не входящих в str2.
s21_size_t s21_strspn(const char *str1, const char *str2); // Вычисляет длину начального сегмента str1, который полностью состоит из символов str2.

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strrchr(const char *str, int ch); //Функция strrchr ищет последнее вхождения символа, код которого указан в аргументе ch, в строке, на которую указывает аргумент str.
char *s21_strncpy (char *dest, const char *src, s21_size_t n); //Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strcpy (char *dest, const char *src); //Копирует строку, на которую указывает src, в dest.
void *s21_memset (void *dest, int c, s21_size_t n); //Копирует символ c (беззнаковый тип) в первые n символов строки, на которую указывает аргумент str.
void *s21_memcpy (void *dest, const void *src, s21_size_t n); //Копирует n символов из src в dest.
void *s21_memmove (void *dest, const void *src, s21_size_t n); //Еще одна функция для копирования n символов из src в dest.

int s21_sprintf(char* str, const char* format, ...);
char *s21_strpbrk(const char *str1, const char *str2); //Функция выполняет поиск первого вхождения в строку str1 любого из символов строки str2
char *s21_strchr(const char *str, int c); //возвращает указатель на первое вхождение младшего байта параметра ch в строку str
void *s21_memchr(const void *str, int c, s21_size_t n); //поиск первого вхождения указанного символа в массиве.
char *s21_strcat(char *dest, const char *src); // объединение строк
char *s21_strncat(char *dest, const char *src, s21_size_t n); //  объединение строк c ограничением длины добавляемой строки
int s21_strcmp(const char *str1, const char *str2); //Сравнивает строку, на которую указывает str1, со строкой, на которую указывает str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n); //Сравнивает не более первых n байтов str1 и str2.
char *s21_strtok(char *str, const char *delim); //Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strstr(const char* str1, const char *str2); //Находит первое вхождение всей строки needle (не включая завершающий нулевой символ), которая появляется в строке haystack.
char *s21_strerror(int errnum); // нужен свой спринтф

void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, size_t start_index);
