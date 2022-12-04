#include <stdarg.h>
#include <stdio.h>

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

int main(void) {
    int d = 0;
    
    switch (flags)
    {
    case 'd':
        d++;
        flag_dD();
        break;
    
    default:
        break;
    }










    return 0;
}

int flag_dD (){

}


