#include "unit_test.h"

START_TEST(strncpy_1) {
    char str_1[50] = "qwerty";
    char str_2[50] = "12345";
    ck_assert_str_eq(strncpy(str_1, str_2, 2*2), s21_strncpy(str_1, str_2, 2*2));
} END_TEST

START_TEST(strncpy_2) {
    char str_1[60] = "50 pdfh";
    char str_2[50] = "HELLO!\n5";
    ck_assert_str_eq(strncpy(str_1, str_2, 5-1), s21_strncpy(str_1, str_2, 5-1));
} END_TEST

START_TEST(strncpy_3) {
    char str_1[50] = "\n/f\f/n";
    char str_2[50] = "55/f/n\f\n";
    ck_assert_str_eq(strncpy(str_1, str_2, 0), s21_strncpy(str_1, str_2, 0));
} END_TEST

START_TEST(strncpy_4) {
    char str_1[20] = "abracadabra ";
    char str_2[] = " 123";
    ck_assert_str_eq(strncpy(str_1, str_2, 10), s21_strncpy(str_1, str_2, 10));
} END_TEST

START_TEST(strncpy_5) {
    char str_1[50] = "s_=+*&/te   ";
    char str_2[50] = "vosem'";
    ck_assert_str_eq(strncpy(str_1, str_2, 6), s21_strncpy(str_1, str_2, 6));
} END_TEST

START_TEST(strncpy_6) {
    char str_1[50] = "8h2f7y10/n5 6";
    char str_2[] = "'40' -l";
    ck_assert_str_eq(strncpy(str_1, str_2, 10/5), s21_strncpy(str_1, str_2, 10/5));
} END_TEST

START_TEST(strncpy_7) {
    char s1[255] = "QWERTY";
    char s2[255] = "Eeee";
    ck_assert_pstr_eq(strncpy(s1, s2, 2), s21_strncpy(s1, s2, 2));
} END_TEST

START_TEST(strncpy_8) {
  char str1[9] = "";
  char str2[] = "def";
  char str3[9] = "";
  int n = 3;
  strncpy(str1, str2, n);
  s21_strncpy(str3, str2, n);
  ck_assert_str_eq(str1, str3);
}
END_TEST

START_TEST(strncpy_9) {
  char str1[9] = "abc";
  char str2[] = "";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_10) {
  char str1[9] = "abc";
  char str2[] = "def";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_11) {
  char str1[9] = "abc";
  char str2[] = "def";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_12) {
  char str1[9] = "ab\nc";
  char str2[] = "def";
  char str3[9] = "ab\nc";
  int n = 9;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_13) {
  char str1[9] = "ab\0c";
  char str2[] = "def";
  char str3[9] = "ab\0c";
  int n = 0;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_14) {
  char str1[9] = "abc";
  char str2[] = "de\0f";
  char str3[9] = "abc";
  int n = 0;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_15) {
  char str1[9] = "abc";
  char str2[] = "de\nf";
  char str3[9] = "abc";
  int n = 7;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_16) {
  char str1[9] = "ab\0c";
  char str2[] = "def";
  char str3[9] = "ab\0c";
  int n = 4;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_17) {
  char str1[9] = "abc";
  char str2[] = "de\0f";
  char str3[9] = "abc";
  int n = 8;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_18) {
  char str1[9] = "";
  char str2[] = "def";
  char str3[9] = "";
  int n = 1;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_19) {
  char str1[9] = "";
  char str2[] = "";
  char str3[9] = "";
  int n = 1;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

START_TEST(strncpy_20) {
  char str1[9] = " ";
  char str2[] = " ";
  char str3[9] = " ";
  int n = 0;
  ck_assert_str_eq(strncpy(str1, str2, n), s21_strncpy(str3, str2, n));
}
END_TEST

Suite * suite_strncpy(void) {
    Suite *s5;
    TCase *tc5;
    s5 = suite_create("s21_STRNCPY");
    tc5 = tcase_create("case_strncpy");
    tcase_add_test(tc5, strncpy_1);
    tcase_add_test(tc5, strncpy_2);
    tcase_add_test(tc5, strncpy_3);
    tcase_add_test(tc5, strncpy_4);
    tcase_add_test(tc5, strncpy_5);
    tcase_add_test(tc5, strncpy_6);
    tcase_add_test(tc5, strncpy_7);
    tcase_add_test(tc5, strncpy_8);
    tcase_add_test(tc5, strncpy_9);
    tcase_add_test(tc5, strncpy_10);
    tcase_add_test(tc5, strncpy_11);
    tcase_add_test(tc5, strncpy_12);
    tcase_add_test(tc5, strncpy_13);
    tcase_add_test(tc5, strncpy_14);
    tcase_add_test(tc5, strncpy_15);
    tcase_add_test(tc5, strncpy_16);
    tcase_add_test(tc5, strncpy_17);
    tcase_add_test(tc5, strncpy_18);
    tcase_add_test(tc5, strncpy_19);
    tcase_add_test(tc5, strncpy_20);
    suite_add_tcase(s5, tc5);
    return s5;
}