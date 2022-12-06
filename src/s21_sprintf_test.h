#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct info {
  va_list args;
  int width;
  int precision;
  int hex_size;
  int zero_padding;
  int point;
  int dash;
  int total_length;
  int sign;
  int is_zero;
  int space;
  int hash;
} s_info;

int s21_ssprintf(const char *format, ...);
void wparg_help(s_info *ints);
void print_res(s_info *ints, const char *str, int temp);
int print_format(s_info *ints, const char *format, int temp);
void print_unsigned(s_info *ints);
void print_numb(s_info *ints);
void print_char(s_info *ints);
void print_str(s_info *ints);
void print_pointer(s_info *ints);
void print_hex(s_info *ints);
void print_hexup(s_info *ints);
void print_per(s_info *ints);
int check_format(const char *format, int temp);
int check_format_letter(const char *format, int temp);
int check_format_letter_2(const char *format, int temp);
int check_percision(s_info *ints, const char *format, int temp);
int check_point(s_info *ints, const char *format, int temp);
int check_wp(s_info *ints, const char *format, int temp);
int check_wparg(s_info *ints, const char *format, int temp);
int n_len(int n);
unsigned int un_len(unsigned int n);
void width_full(s_info *ints, int flag);
void prec_ful(s_info *ints);
int put_str(s_info *ints, char *s);
void scanndase(s_info *ints, unsigned long long numb);
void point_b(s_info *ints, unsigned long long numb, char x);
void put(int n, s_info *ints);
void putnbr(unsigned n, s_info *ints);
void litle_if(s_info *ints, int *numb);
void else_if(s_info *ints, int *numb);
int str_else(char *s, s_info *ints);
void hexup_help(s_info *ints, unsigned int hexup);
void hex_help(s_info *ints, unsigned int hexal);
void numb_if(int numb, s_info *ints);
void unsint_if(unsigned int uns, s_info *ints);
int check_help(s_info *ints, const char *format, int temp);
size_t s21strlen(const char *str);
