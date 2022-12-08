#include "s21_sprintf_test.h"
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
    ints->full_buf[CHAR_PATTERN] = 0;
    return (ints);
}

int s21_ssprintf(char *str, const char *format, ...) {
    int i = -1;
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
            // strcat(str, format);
            // printf("%d\n", i);
        } else {
            strcat(ints->full_buf, &format[i]);
            // result[CHAR_PATTERN] += write(1, &format[i],1);
            // printf("%c", format[i]);
            // strcat(str, ints->full_buf);
        }
    }
    // printf("%s", ints->full_buf);
    // strcat(str, format);
    // result[CHAR_PATTERN] += ints->total_length;
    strcat(str, ints->full_buf);
    va_end(ints->args);
    free(ints);
    return 0;
}

void print_res(s_info *ints, const char *str, int temp) {
    if (str[temp] == 'c') print_char(ints);
    if (str[temp] == 's') print_str(ints);
    if (str[temp] == 'p') print_pointer(ints);
    if (str[temp] == 'd' || str[temp] == 'i') print_numb(ints);
    if (str[temp] == 'f') print_float(ints);
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
    if (format[temp] == '*')
        temp = check_wparg(ints, format, temp);
    else
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
                strcat(ints->full_buf, "0");
                // ints->total_length += write(1, "0", 1);
            } else {
                strcat(ints->full_buf, "0");
                // ints->total_length += write(1, "0", 1);
            }
        } else {
            itoa(uns, ints->full_buf, 10);
            // putnbr(uns, ints);
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
        fpart = fpart > 0 ? floor(fpart + 0.5f) : ceil(fpart - 0.5f);
        fpart = fpart / 10.0f;
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

void print_float(s_info *ints) {
    double numb_fl = 0;
    int len;
    char pattern_f_d[9000] = {0};
    numb_fl = va_arg(ints->args, double);
    ftoa(numb_fl, pattern_f_d, 5);
    if (pattern_f_d) len = s21strlen(pattern_f_d);
    if (ints->width && pattern_f_d && ints->precision < len && ints->point &&
        ints->precision >= 0)
        ints->width -= ints->precision;
    else if (ints->width && pattern_f_d)
        ints->width -= len;
    if (!pattern_f_d && ints->point && ints->precision < 6)
        ints->width -= ints->precision;
    else if (!pattern_f_d)
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
                strcat(ints->full_buf, " ");
            } else {
                strcat(ints->full_buf, "0");
            }
        } else {
            itoa(numb, tolik_n, 10);
            strcat(ints->full_buf, tolik_n);
            // printf("%s", ints->full_buf);
        }
        if (ints->width > 0 && ints->dash) {
            width_full(ints, 0);
        }
    }
}

void print_char(s_info *ints) {
    char c;
    c = va_arg(ints->args, int);
    if (ints->width) ints->width -= 1;
    if (ints->width > 0 && !ints->dash) width_full(ints, 0);
    strcat(ints->full_buf, &c);
    // ints->total_length += write(1, &c, 1);
    if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_str(s_info *ints) {
    char *str;
    int len;
    str = va_arg(ints->args, char *);
    if (str) len = s21strlen(str);
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
    strcat(ints->full_buf, "0x");
    // ints->total_length += write(1, "0x", 2);
    if (points != 0 || !ints->point) point_b(ints, points, 'x');
    if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

void print_hex(s_info *ints) {
    unsigned int hex;
    hex = va_arg(ints->args, unsigned int);
    ints->hex_size = 0;
    scanndase(ints, hex);
    if (ints->precision == 0 && hex == 0 && !ints->width && ints->point) {
        ints->is_zero = 1;
    } else {
        hex_help(ints, hex);
        if (hex == 0 && ints->precision == 0 && ints->point) {
            if (ints->width) {
                strcat(ints->full_buf, " ");
                // ints->total_length += write(1, " ", 1);
            } else {
                strcat(ints->full_buf, "0");
                // ints->total_length += write(1, "0", 1);
            }
        } else {
            point_b(ints, hex, 'x');
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
                strcat(ints->full_buf, " ");
                // ints->total_length += write(1, " ", 1);
            } else {
                strcat(ints->full_buf, "0");
                // ints->total_length += write(1, "0", 1);
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
    strcat(ints->full_buf, "%");
    // ints->total_length += write(1, "%", 1);
    if (ints->width > 0 && ints->dash) width_full(ints, 0);
}

int check_format(const char *format, int temp) {
    if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
        format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
        format[temp] != 'u' && format[temp] != 'x' && format[temp] != 'X' &&
        format[temp] != '%' && format[temp] != '*' &&
        !(format[temp] >= '1' && format[temp] <= '9')) {
        return 1;
    }
    return 0;
}

int check_format_letter(const char *format, int temp) {
    if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
        format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
        format[temp] != 'u' && format[temp] != 'x' && format[temp] != 'X' &&
        format[temp] != '%' && (format[temp] >= '0' && format[temp] <= '9')) {
        return 1;
    }
    return 0;
}

int check_format_letter_2(const char *format, int temp) {
    if (format[temp] != 'c' && format[temp] != 's' && format[temp] != 'p' &&
        format[temp] != 'd' && format[temp] != 'i' && format[temp] != 'f' &&
        format[temp] != 'u' && format[temp] != 'x' && format[temp] != 'X' &&
        format[temp] != '%' && format[temp] != '.' &&
        (format[temp] >= '0' && format[temp] <= '9')) {
        return 1;
    }
    return 0;
}

int check_percision(s_info *ints, const char *format, int temp) {
    int perc;
    if (format[temp] == '.') {
        ints->point = 1;
        temp++;
        if (format[temp] == '*') {
            perc = va_arg(ints->args, int);
            if (perc < 0) {
                ints->precision = 0;
                ints->point = 0;
            } else {
                ints->precision = perc;
            }
            temp++;
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
        if (format[temp] == '*') {
            perc = va_arg(ints->args, int);
            ints->precision = perc;
            temp++;
        } else {
            while (check_format_letter(format, temp)) {
                ints->width = (ints->width * 10) + (format[temp] - 48);
                temp++;
            }
            temp = check_percision(ints, format, temp);
        }
    } else {
        while (check_format_letter(format, temp)) {
            ints->precision = (ints->precision * 10) + (format[temp] - 48);
            temp++;
        }
    }
    return temp;
}

int check_wp(s_info *ints, const char *format, int temp) {
    if (!ints->point) {
        while (check_format_letter_2(format, temp)) {
            ints->width = (ints->width * 10) + (format[temp] - 48);
            temp++;
        }
        temp = check_percision(ints, format, temp);
    } else {
        while (check_format_letter(format, temp)) {
            ints->precision = (ints->precision * 10) + (format[temp] - 48);
            temp++;
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
        temp = check_point(ints, format, temp);
    } else {
        wparg_help(ints);
        temp++;
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
    int i = -1;
    if (!flag) {
        while (++i < ints->width) {
            strcat(ints->full_buf, " ");
        }
    } else {
        while (++i < ints->width) {
            strcat(ints->full_buf, "0");
        }
    }
}

void prec_ful(s_info *ints) {
    int i = -1;
    while (++i < ints->precision) {
        strcat(ints->full_buf, "0");
        // ints->total_length += write(1, "0", 1);
    }
}

int put_str(s_info *ints, char *s) {
    int i = 0;
    if (!s) {
        if (!ints->point) {
            strcat(ints->full_buf, "(null)");
            // ints->total_length += write(1, "(null)", 6);
        } else {
            put_str(ints, "(null)");
            ints->total_length += ints->precision;
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

void point_b(s_info *ints, unsigned long long numb, char x) {
    char *base;
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
        strcat(ints->full_buf, base);
        // ints->total_length += write(1, &base[numb], 1);
    }
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

// void put(int n, s_info *ints) {
//   if (n < 10) {
//     n += 48;

//     // printf("%s", tolik_n);
//     // ints->total_length += write(1, &n, 1);
//     // printf("%d\n", ints->total_length);
//   } else {
//     put(n / 10, ints);
//     put(n % 10, ints);
//   }
// }

// void putnbr(unsigned n, s_info *ints) {
//   if (n < 10) {
//     n += 48;
//     ints->total_length += write(1, &n, 1);
//   } else {
//     putnbr(n / 10, ints);
//     putnbr(n % 10, ints);
//   }
// }

void litle_if(s_info *ints, int *numb) {
    strcat(ints->full_buf, "-");
    // ints->total_length += write(1, "-", 1);
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
            strcat(ints->full_buf, "-");
            // ints->total_length += write(1, "-", 1);
            width_full(ints, ints->zero_padding);
        } else {
            width_full(ints, 0);
            strcat(ints->full_buf, "-");
            // ints->total_length += write(1, "-", 1);
        }
    } else {
        strcat(ints->full_buf, "-");
    }
    // ints->total_length += write(1, "-", 1);
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
        while (s[i] != '\0' && i != ints->precision) {
            // write(1, &s[i], 1);
            strcat(ints->full_buf, &s[i]);
            // printf("%s\n", s);
            i++;
        }
    } else {
        strcat(ints->full_buf, s);
        // printf("%s\n", s);
        i++;
    }
    return i;
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
        strcat(ints->full_buf, "0X");
        // ints->total_length += write(1, "0X", 2);
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
        strcat(ints->full_buf, "0x");
        // ints->total_length += write(1, "0x", 2);
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
        strcat(ints->full_buf, "+");
        // ints->total_length += write(1, "+", 1);
    } else if (ints->space && numb >= 0) {
        strcat(ints->full_buf, " ");
        // ints->total_length += write(1, " ", 1);
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
    }
}

int check_help(s_info *ints, const char *format, int temp) {
    while (check_format_letter(format, temp)) {
        ints->precision = (ints->precision * 10) + (format[temp] - 48);
        temp++;
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
