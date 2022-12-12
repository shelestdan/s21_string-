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
  ints->numb_fl = 0;
  ints->j_save_format = 0;
  ints->full_buf[CHAR_PATTERN] = 0;
  ints->flag_f_float = 0;
  ints->flag_o = 0;
  ints->flag_e = 0;
  return (ints);
}

int s21_sprintf(char *str, const char *format, ...) {
  int i = -1;
  *str = 0;
  s_info *ints;
  ints = (s_info *)malloc(sizeof(s_info));
  if (!ints) {
    return -1;
  }
  initialise(ints);
  ints->total_length = 0;
  va_start(ints->args, format);
  while (format[++i]) {
    if (format[i] == '%') {
      i = print_format(ints, format, ++i);
    } else {
      // printf("%s", ints->full_buf);
      ints->j_save_format = s21strlen(ints->full_buf);
      ints->full_buf[ints->j_save_format] = format[i];
      ints->j_save_format++;
    }
  }
  // printf("%s", ints->full_buf);
  s_strcat(str, ints->full_buf);
  va_end(ints->args);
  free(ints);
  return ints->j_save_format;
}

void print_res(s_info *ints, const char *str, int temp) {
  if (str[temp] == 'c') print_char(ints);
  if (str[temp] == 's') print_str(ints);
  if (str[temp] == 'e') {
    ints->flag_e++;
    flag_exp(ints);
  }
  if (str[temp] == 'g' || str[temp] == 'G') s21_sprintf_g(ints);
  if (str[temp] == 'p') print_pointer(ints);
  if (str[temp] == 'd' || str[temp] == 'i') print_numb(ints);
  if (str[temp] == 'f') {
    ints->flag_f_float++;
    print_float(ints);
  }
  if (str[temp] == 'o') {
    ints->flag_o++;
    print_hex(ints);
  }
  if (str[temp] == 'u') print_unsigned(ints);
  if (str[temp] == 'x') print_hex(ints);
  if (str[temp] == 'X') print_hexup(ints);
  if (str[temp] == '%') print_per(ints);
}

int print_format(s_info *ints, const char *format, int temp) {
  while (check_format(format, temp)) {
    if (format[temp] == '-') ints->dash = 1;
    if (format[temp] == '+') ints->sign = 1;
    if (format[temp] == ' ') ints->space = 1;
    if (format[temp] == '0' && !ints->point) ints->zero_padding = 1;
    if (format[temp] == '#') ints->hash = 1;
    if (format[temp] == '.') ints->point = 1;
    temp++;
  }
  if (format[temp] == '*') temp = check_wparg(ints, format, temp);
  if (format[temp] == 'n') {
    int c;
    c = (int)s21strlen(ints->full_buf);
    *va_arg(ints->args, int *) = c;
  } else
    temp = check_wp(ints, format, temp);
  print_res(ints, format, temp);
  initialise(ints);
  return (temp);
}

void print_unsigned(s_info *ints) {
  unsigned int uns;
  uns = va_arg(ints->args, unsigned int);
  if (ints->precision == 0 && uns == 0 && !ints->width && ints->point) {
    ints->is_zero = 1;
  } else {
    unsint_if(uns, ints);
    if (uns == 0 && ints->precision == 0 && ints->point) {
      if (ints->width) {
        s_strcat(ints->full_buf, "0");
        ints->j_save_format++;
      } else {
        s_strcat(ints->full_buf, "0");
        ints->j_save_format++;
      }
    } else {
      itoa(uns, ints->full_buf, 10);
    }
    if (ints->width > 0 && ints->dash) {
      width_full(ints, 0);
    }
  }
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

char *s_strcat(char *dest, const char *src) {
  size_t start = s21strlen(dest);
  size_t end = s21strlen(src);
  // printf("%ld %ld", start, end);
  for (size_t i = start, j = 0; j <= end; i++, j++) {
    dest[i] = src[j];
    // printf("%c\n", dest[i]);
  }
  // printf("%s\n", dest);
  return dest;
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

void ftoa(float n, char *res, s_info *ints) {
  if (ints->precision == 0 && !ints->flag_e) ints->precision = 6;
  int ipart = (int)n;
  float fpart = n - (float)ipart;
  int i = intToStr(ipart, res, 0);
  if (i == 0) i++;
  if (ints->precision != 0) {
    if (ipart == 0) res[0] = '0';
    res[i] = '.';
    fpart = fpart * pow(10, ints->precision);
    fpart = fpart * 10.0f;
    fpart = fpart > 0 ? floor(fpart + 0.5f) : ceil(fpart - 0.5f);
    fpart = fpart / 10.0f;
    intToStr((int)fpart, res + i + 1, ints->precision);
  }
}

int flag_exp_g(s_info *ints, double b) {
  double val = b;
  int e = 0;
  if (val >= 10) {
    while (val >= 10) {
      val /= 10.0;
      e += 1;
    }
  } else if (val < 1 && val != 0) {
    while (val < 1) {
      val *= 10;
      e -= 1;
    }
  }
  val = round(val * pow(10, ints->precision)) * pow(10, -(ints->precision));
  if (val >= 10) {
    val /= 10.0;
    e += 1;
  } else if (val < 1 && val != 0) {
    val *= 10;
    e -= 1;
  }
  // printf("%d", e);
  return e;
}

void s21_sprintf_g(s_info *ints) {
  double b = 0;
  char pattern_g[CHAR_PATTERN] = {0};
  b = va_arg(ints->args, double);
  if (ints->precision == 0)
    ints->precision = 6;
  else if (ints->precision == 1)
    ints->precision = 1;
  long double b_copy = b;
  if (b_copy < 0) b_copy *= -1;
  int e = flag_exp_g(ints, b);
  if (ints->precision > e && e >= -4) {
    ftoa(b, pattern_g, ints);
    s_strcat(ints->full_buf, pattern_g);
  } else {
    char buff[CHAR_PATTERN] = {0};
    int pow = 0;
    double val = b;
    char sign = (int)val == 0 ? '-' : '+';
    if ((int)val - val) {
      while ((int)val == 0) {
        pow++;
        val *= 10;
      }
    } else {
      sign = '+';
    }
    while ((int)val / 10 != 0) {
      pow++;
      val /= 10;
    }
    ftoa(val, buff, ints);
    s21_size_t i = s21strlen(buff);
    buff[i] = 'e';
    buff[i + 1] = sign;
    buff[i + 3] = pow % 10 + '0';
    pow /= 10;
    buff[i + 2] = pow % 10 + '0';
    buff[i + 4] = '\0';
    s_strcat(ints->full_buf, buff);
    ints->j_save_format++;
  }
}

void print_float(s_info *ints) {
  double numb_fl = 0;
  int len;
  char pattern_f_d[9000] = {0};
  numb_fl = va_arg(ints->args, double);
  ftoa(numb_fl, pattern_f_d, ints);
  len = s21strlen(pattern_f_d);
  if (ints->width && ints->precision < len && ints->point &&
      ints->precision >= 0)
    ints->width -= ints->precision;
  else if (ints->width)
    ints->width -= len;
  if (ints->point && ints->precision < 6)
    ints->width -= ints->precision;
  else 
    ints->width -= 6;
  if (ints->width > 0 && !ints->dash) width_full(ints, 0);
  ints->total_length += put_str(ints, pattern_f_d);
  if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_numb(s_info *ints) {
  int numb;
  char tolik_n[9000] = {0};
  numb = va_arg(ints->args, int);
  if (ints->precision == 0 && numb == 0 && !ints->width && ints->point) {
    ints->is_zero = 1;
  } else {
    numb_if(numb, ints);
    else_if(ints, &numb);
    if (numb == 0 && ints->precision == 0 && ints->point) {
      if (ints->width) {
        s_strcat(ints->full_buf, " ");
        ints->j_save_format++;
      } else {
        s_strcat(ints->full_buf, "0");
        ints->j_save_format++;
      }
    } else {
      itoa(numb, tolik_n, 10);
      s_strcat(ints->full_buf, tolik_n);
      ints->j_save_format++;
    }
    if (ints->width > 0 && ints->dash) {
      width_full(ints, 0);
    }
  }
}

void print_char(s_info *ints) {
  char c;
  ints->j_save_format++;
  c = va_arg(ints->args, int);
  char str1[CHAR_PATTERN] = {c, '\0'};
  s_strcat(ints->full_buf, str1);
  if (ints->width) ints->width -= 1;
  if (ints->width > 0 && !ints->dash) width_full(ints, 0);
  if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_str(s_info *ints) {
  char *str = {0};
  int len;
  str = va_arg(ints->args, char *);
  if (str) {
    len = s21strlen(str);
  }
  ints->j_save_format += len;
  ints->j_save_format++;
  if (ints->width && str && ints->precision < len && ints->point &&
      ints->precision >= 0)
    ints->width -= ints->precision;
  else if (ints->width && str)
    ints->width -= len;
  if (!str && ints->point && ints->precision < 6)
    ints->width -= ints->precision;
  else if (!str)
    ints->width -= 6;
  if (ints->width > 0 && !ints->dash) width_full(ints, 0);
  // printf("%d", ints->total_length);
  ints->total_length += put_str(ints, str);

  if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_pointer(s_info *ints) {
  unsigned long points;
  points = va_arg(ints->args, unsigned long);
  ints->hex_size = 0;
  ints->width -= 2;
  if (points != 0 || !ints->point) scanndase(ints, points);
  if (ints->width) ints->width -= !ints->hex_size;
  if (ints->width > 0 && !ints->dash) width_full(ints, ints->zero_padding);
  s_strcat(ints->full_buf, "0x");
  ints->j_save_format++;
  if (points != 0 || !ints->point) point_b(ints, points, 'x');
  if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_hex(s_info *ints) {
  unsigned int hex;
  hex = va_arg(ints->args, unsigned int);
  ints->hex_size = 0;

  if (ints->flag_o) {
    scanndase_o(ints, hex);
  } else {
    scanndase(ints, hex);
  }
  if (ints->precision == 0 && hex == 0 && !ints->width && ints->point) {
    ints->is_zero = 1;
  } else {
    hex_help(ints, hex);
    if (hex == 0 && ints->precision == 0 && ints->point) {
      if (ints->width) {
        s_strcat(ints->full_buf, " ");
        ints->j_save_format++;
      } else {
        s_strcat(ints->full_buf, "0");
        ints->j_save_format++;
      }
    } else {
      if (ints->flag_o) {
        point_o(ints, hex, 'o');
      } else {
        point_b(ints, hex, 'x');
      }
    }
    if (ints->width > 0 && ints->dash) {
      width_full(ints, 0);
    }
  }
}

void print_hexup(s_info *ints) {
  unsigned int hexup;
  hexup = va_arg(ints->args, unsigned int);
  ints->hex_size = 0;
  scanndase(ints, hexup);
  if (ints->precision == 0 && hexup == 0 && !ints->width && ints->point) {
    ints->is_zero = 1;
  } else {
    hexup_help(ints, hexup);
    if (hexup == 0 && ints->precision == 0 && ints->point) {
      if (ints->width) {
        s_strcat(ints->full_buf, " ");
        ints->j_save_format++;
      } else {
        s_strcat(ints->full_buf, "0");
        ints->j_save_format++;
      }
    } else {
      point_b(ints, hexup, 'X');
    }
    if (ints->width > 0 && ints->dash) {
      width_full(ints, 0);
    }
  }
}

void print_per(s_info *ints) {
  if (ints->width) ints->width -= 1;
  if (ints->width > 0 && !ints->dash) width_full(ints, ints->zero_padding);
  s_strcat(ints->full_buf, "%");
  ints->j_save_format++;
  if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

int check_format(const char *format, int temp) {
  if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
      format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
      format[temp] != 'g' && format[temp] != 'G' && format[temp] != 'e' &&
      format[temp] != 'u' && format[temp] != 'x' && format[temp] != 'X' &&
      format[temp] != '%' && format[temp] != '*' && format[temp] != 'n' &&
      format[temp] != 'o' && !(format[temp] >= '1' && format[temp] <= '9')) {
    return 1;
  }
  return 0;
}

int check_format_letter(const char *format, int temp) {
  if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
      format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
      format[temp] != 'g' && format[temp] != 'G' && format[temp] != 'e' &&
      format[temp] != 'n' && format[temp] != 'u' && format[temp] != 'x' &&
      format[temp] != 'X' && format[temp] != 'o' && format[temp] != '%' &&
      (format[temp] >= '0' && format[temp] <= '9')) {
    return 1;
  }
  return 0;
}

int check_format_letter_2(const char *format, int temp) {
  if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
      format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
      format[temp] != 'g' && format[temp] != 'G' && format[temp] != 'e' &&
      format[temp] != 'u' && format[temp] != 'x' && format[temp] != 'X' &&
      format[temp] != 'n' && format[temp] != 'o' && format[temp] != '%' &&
      format[temp] != '.' && (format[temp] >= '0' && format[temp] <= '9')) {
    return 1;
  }
  return 0;
}

int check_percision(s_info *ints, const char *format, int temp) {
  int perc;
  if (format[temp] == '.') {
    ints->point = 1;
    temp++;
    ints->j_save_format++;
    if (format[temp] == '*') {
      perc = va_arg(ints->args, int);
      if (perc < 0) {
        ints->precision = 0;
        ints->point = 0;
      } else {
        ints->precision = perc;
        ints->j_save_format++;
      }
      temp++;
      ints->j_save_format++;
    } else {
      temp = check_help(ints, format, temp);
    }
  }
  return temp;
}

int check_point(s_info *ints, const char *format, int temp) {
  int perc;
  if (format[temp] == '.') {
    ints->point = 1;
    temp++;
    ints->j_save_format++;
    if (format[temp] == '*') {
      perc = va_arg(ints->args, int);
      ints->precision = perc;
      ints->j_save_format++;
      temp++;
      ints->j_save_format++;
    } else {
      while (check_format_letter(format, temp)) {
        ints->width = (ints->width * 10) + (format[temp] - 48);
        temp++;
        ints->j_save_format++;
      }
      temp = check_percision(ints, format, temp);
    }
  } else {
    while (check_format_letter(format, temp)) {
      ints->precision = (ints->precision * 10) + (format[temp] - 48);
      temp++;
      ints->j_save_format++;
    }
  }
  return temp;
}

int check_wp(s_info *ints, const char *format, int temp) {
  if (!ints->point) {
    while (check_format_letter_2(format, temp)) {
      ints->width = (ints->width * 10) + (format[temp] - 48);
      temp++;
      ints->j_save_format++;
    }
    temp = check_percision(ints, format, temp);
  } else {
    while (check_format_letter(format, temp)) {
      ints->precision = (ints->precision * 10) + (format[temp] - 48);
      temp++;
      ints->j_save_format++;
    }
  }
  return temp;
}

int check_wparg(s_info *ints, const char *format, int temp) {
  int width;

  if (!ints->point) {
    width = va_arg(ints->args, int);
    if (width < 0) {
      ints->dash = 1;
      width *= -1;
    }
    ints->width = width;
    temp++;
    ints->j_save_format++;
    temp = check_point(ints, format, temp);
  } else {
    wparg_help(ints);
    temp++;
    ints->j_save_format++;
  }
  return (temp);
}

int n_len(int n) {
  int len = 1;
  if (n == -2147483648) {
    return 1;
  }
  if (n < 0) {
    n *= -1;
    len++;
  }
  while (n > 9) {
    n /= 10;
    len++;
  }
  return len;
}

unsigned int un_len(unsigned int n) {
  unsigned int len = 1;
  while (n > 9) {
    n /= 10;
    len++;
  }
  return len;
}

void width_full(s_info *ints, int flag) {
  char buff_space[100] = " ";
  char buff_null[100] = "0";
  size_t l = s21strlen(ints->full_buf);
  if (!flag) {
    for (size_t i = l; i < l + ints->width; i++) {
      ints->full_buf[i] = buff_space[0];
      ints->j_save_format++;
    }
    // printf("%s", ints->full_buf);
  } else {
    // while (++i < ints->width) {
    s_strcat(ints->full_buf, buff_null);
    ints->j_save_format++;
  }
  // }
}

void prec_ful(s_info *ints) {
  int i = -1;
  while (++i < ints->precision) {
    s_strcat(ints->full_buf, "0");
    ints->j_save_format++;
  }
}

int put_str(s_info *ints, char *s) {
  int i = 0;
  if (!s) {
    if (!ints->point) {
      s_strcat(ints->full_buf, "(null)");
      ints->j_save_format++;
    } else {
      put_str(ints, "(null)");
      ints->total_length += ints->precision;
      ints->j_save_format++;
    }
  } else {
    i = str_else(s, ints);
  }
  return i;
}

void scanndase(s_info *ints, unsigned long long numb) {
  if (numb > 15) {
    scanndase(ints, numb / 16);
    scanndase(ints, numb % 16);
  } else {
    ints->hex_size += 1;
  }
}

void scanndase_o(s_info *ints, unsigned long long numb) {
  if (ints->flag_o) {
    if (numb > 7) {
      scanndase_o(ints, numb / 8);
      scanndase_o(ints, numb % 8);
    } else {
      ints->hex_size += 1;
    }
  }
}

void point_b(s_info *ints, unsigned long long numb, char x) {
  char *base;
  int i = 0;
  char l[100] = {0};
  if (x == 'x') {
    base = "0123456789abcdef";
  }
  if (x == 'X') {
    base = "0123456789ABCDEF";
  }
  if (numb > 15) {
    point_b(ints, numb / 16, x);
    point_b(ints, numb % 16, x);
  } else {
    l[i] = base[numb];
    i++;
  }
  s_strcat(ints->full_buf, l);
  ints->j_save_format++;
}

void point_o(s_info *ints, unsigned long long numb, char o) {
  char *base;
  int i = 0;
  char l[100] = {0};
  if (o == 'o') {
    base = "01234567";
  }
  if (numb > 7) {
    point_o(ints, numb / 8, o);
    point_o(ints, numb % 8, o);
  } else {
    l[i] = base[numb];
    i++;
  }
  s_strcat(ints->full_buf, l);
  ints->j_save_format++;
}

char *itoa(int value, char *result, int base) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }
  char *ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;
  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + (tmp_value - value * base)];
  } while (value);
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

void litle_if(s_info *ints, int *numb) {
  s_strcat(ints->full_buf, "-");
  ints->j_save_format++;
  *numb = 147483648;
  if (ints->width > 0 && !ints->dash) {
    width_full(ints, ints->zero_padding);
  }
  if (ints->precision > 0) {
    prec_ful(ints);
  }
  *numb *= -1;
}

void if_next(s_info *ints, int *numb) {
  if (ints->width > 0 && !ints->dash && !ints->zero_padding)
    width_full(ints, ints->zero_padding);
  if (ints->width > 0 && !ints->dash && ints->zero_padding) {
    if (!ints->point) {
      s_strcat(ints->full_buf, "-");
      ints->j_save_format++;
      width_full(ints, ints->zero_padding);
    } else {
      width_full(ints, 0);
      s_strcat(ints->full_buf, "-");
      ints->j_save_format++;
    }
  } else {
    s_strcat(ints->full_buf, "-");
    ints->j_save_format++;
  }
  if (ints->precision > 0) prec_ful(ints);
  *numb *= -1;
}

void else_if(s_info *ints, int *numb) {
  if (*numb == -2147483648) {
    litle_if(ints, numb);
  } else if (*numb < 0) {
    if_next(ints, numb);
  } else {
    if (ints->width > 0 && !ints->dash && !ints->point) {
      width_full(ints, ints->zero_padding);
    } else if (ints->width > 0 && !ints->dash && ints->point) {
      width_full(ints, 0);
    }
    if (ints->precision > 0) {
      prec_ful(ints);
    }
  }
}

int str_else(char *s, s_info *ints) {
  int i = 0;
  if (ints->point) {
    if (i != ints->precision) {
      if (ints->flag_f_float) {
        s_strcat(ints->full_buf, s);
        ints->j_save_format++;
      } else {
        s_strncat(ints->full_buf, s, ints->precision);
        ints->j_save_format++;
      }
    }
  } else {
    // printf("%s", s);
    //  printf("%s", ints->full_buf);
    s_strcat(ints->full_buf, s);
    // printf("%s", ints->full_buf);
    ints->j_save_format++;
  }
  return i;
}

char *s_strncat(char *dest, const char *src, s21_size_t n) {
  size_t start = s21strlen(dest);
  size_t end = s21strlen(src);
  if (n > end) n = end;
  for (size_t i = start, j = 0; j < n; i++, j++) {
    dest[i] = src[j];
    // printf("%c", dest[i]);
  }
  // printf("%s", dest);
  // dest[i+1] = '\0';
  // printf("%s", dest);
  return dest;
}

void flag_exp(s_info *ints) {
  double val = va_arg(ints->args, double);
  char buff[CHAR_PATTERN] = {0};
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';
  if ((int)val - val) {
    while ((int)val == 0) {
      pow++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }
  ftoa(val, buff, ints);
  s21_size_t i = s21strlen(buff);
  buff[i] = 'e';
  buff[i + 1] = sign;
  buff[i + 3] = pow % 10 + '0';
  pow /= 10;
  buff[i + 2] = pow % 10 + '0';
  buff[i + 4] = '\0';
  s_strcat(ints->full_buf, buff);
  ints->j_save_format++;
}

void hexup_help(s_info *ints, unsigned int hexup) {
  if (ints->precision) ints->precision -= ints->hex_size;
  if (ints->width > 0 && ints->precision > 0) {
    ints->width -= ints->hex_size + ints->precision;
  } else if (ints->width > 0) {
    ints->width -= ints->hex_size;
  }
  if (ints->width > 0 && !ints->dash && !ints->point) {
    width_full(ints, ints->zero_padding);
  } else if (ints->width > 0 && !ints->dash && ints->point) {
    width_full(ints, 0);
  }
  if (ints->hash && hexup) {
    s_strcat(ints->full_buf, "0X");
    ints->j_save_format++;
    ints->width -= 2;
  }
  if (ints->precision > 0) prec_ful(ints);
}

void hex_help(s_info *ints, unsigned int hexal) {
  if (ints->precision) {
    ints->precision -= ints->hex_size;
  }
  if (ints->width > 0 && ints->precision > 0) {
    ints->width -= ints->hex_size + ints->precision;
  } else if (ints->width > 0) {
    ints->width -= ints->hex_size;
  }
  if (ints->width > 0 && !ints->dash && !ints->point) {
    width_full(ints, ints->zero_padding);
  } else if (ints->width > 0 && !ints->dash && ints->point) {
    width_full(ints, 0);
  }
  if (ints->hash && hexal) {
    s_strcat(ints->full_buf, "0x");
    ints->j_save_format++;
    ints->width -= 2;
  }
  if (ints->precision > 0) {
    prec_ful(ints);
  }
}

void numb_if(int numb, s_info *ints) {
  if (ints->precision > 0 && numb >= 0) {
    ints->precision -= n_len(numb);
  } else if (ints->precision > 0 && numb < 0) {
    ints->precision -= n_len(numb) - 1;
  }
  if (ints->width > 0 && ints->precision > 0) {
    ints->width -= n_len(numb) + ints->precision;
  } else if (ints->width > 0) {
    ints->width -= n_len(numb);
  }
  if (ints->sign && numb >= 0) {
    s_strcat(ints->full_buf, "+");
    ints->j_save_format++;
  } else if (ints->space && numb >= 0) {
    s_strcat(ints->full_buf, " ");
    ints->j_save_format++;
  }
}

void unsint_if(unsigned int uns, s_info *ints) {
  if (ints->precision > 0) ints->precision -= n_len(uns);
  if (ints->width > 0 && ints->precision > 0)
    ints->width -= n_len(uns) + ints->precision;
  else if (ints->width > 0)
    ints->width -= n_len(uns);
  if (ints->width > 0 && !ints->dash && !ints->point)
    width_full(ints, ints->zero_padding);
  else if (ints->width > 0 && !ints->dash && ints->point)
    width_full(ints, 0);
  if (ints->precision > 0) prec_ful(ints);
}

void wparg_help(s_info *ints) {
  int perc;
  perc = va_arg(ints->args, int);
  if (perc < 0) {
    ints->precision = 0;
    ints->point = 0;
  } else {
    ints->precision = perc;
    ints->j_save_format++;
  }
}

int check_help(s_info *ints, const char *format, int temp) {
  while (check_format_letter(format, temp)) {
    ints->precision = (ints->precision * 10) + (format[temp] - 48);
    temp++;
    ints->j_save_format++;
  }
  return temp;
}

size_t s21strlen(const char *str) {
  size_t i;
  i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return (i);
}
