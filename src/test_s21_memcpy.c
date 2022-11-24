#include "unit_test.h"

START_TEST(memcpy_1) {
    char str_5[3] = "a\n\0";
    char str_6[3] = "\0";
    ck_assert_str_eq(memcpy(str_5, str_6, 2), s21_memcpy(str_5, str_6, 2));
} END_TEST

START_TEST(memcpy_2) {
    char str_1[] = "\0";
    char str_2[] = " ";
    ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 1));
} END_TEST

START_TEST(memcpy_3) {
    char str_1[] = "copy_! ";
    char str_2[] = "n66";
    ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
} END_TEST

START_TEST(memcpy_4) {
    char str_1[] = "\n/n";
    char str_2[] = "-55";
    ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
} END_TEST

START_TEST(memcpy_5) {
    char str_1[] = "5656";
    char str_2[] = "\0\f";
    ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
} END_TEST

START_TEST(memcpy_6) {
    char str_1[] = "%hf*-5";
    char str_2[] = "\0\f";
    ck_assert_str_eq(memcpy(str_1, str_2, 2), s21_memcpy(str_1, str_2, 5));
} END_TEST

START_TEST(memcpy_7) {
    char s1[255] = "QWERTY";
    char s2[255] = "E";
    ck_assert_pstr_eq(memcpy(s1, s2, 6), s21_memcpy(s1, s2, 6));
} END_TEST

START_TEST(memcpy_8) {
  char str1[9] = "";
  char str2[] = "def";
  char str3[9] = "";
  int n = 3;
  memcpy(str1, str2, n);
  s21_memcpy(str3, str2, n);
  ck_assert_str_eq(str1, str3);
}
END_TEST

START_TEST(memcpy_9) {
  char str1[9] = "abc";
  char str2[] = "";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_10) {
  char str1[9] = "abc";
  char str2[] = "def";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_11) {
  char str1[9] = "abc";
  char str2[] = "def";
  char str3[9] = "abc";
  int n = 1;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_12) {
  char str1[9] = "ab\nc";
  char str2[] = "def";
  char str3[9] = "ab\nc";
  int n = 4;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_13) {
  char str1[9] = "ab\0c";
  char str2[] = "def";
  char str3[9] = "ab\0c";
  int n = 0;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_14) {
  char str1[9] = "abc";
  char str2[] = "de\0f";
  char str3[9] = "abc";
  int n = 0;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_15) {
#line 664
  char str1[9] = "abc";
  char str2[] = "de\nf";
  char str3[9] = "abc";
  int n = 0;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_16) {
  char str1[9] = "ab\0c";
  char str2[] = "def";
  char str3[9] = "ab\0c";
  int n = 4;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_17) {
  char str1[9] = "abc";
  char str2[] = "de\0f";
  char str3[9] = "ab\0c";
  int n = 3;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_18) {
  char str1[9] = "";
  char str2[] = "def";
  char str3[9] = "";
  int n = 1;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_19) {
  char str1[9] = "";
  char str2[] = "";
  char str3[9] = "";
  int n = 1;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

START_TEST(memcpy_20) {
  char str1[9] = " ";
  char str2[] = " ";
  char str3[9] = " ";
  int n = 0;
  ck_assert_str_eq(memcpy(str1, str2, n), s21_memcpy(str3, str2, n));
}
END_TEST

Suite * suite_memcpy(void) {
    Suite *s1;
    TCase *tc1;
    s1 = suite_create("s21_MEMCPY");
    tc1 = tcase_create("case_memcpy");
    tcase_add_test(tc1, memcpy_1);
    tcase_add_test(tc1, memcpy_2);
    tcase_add_test(tc1, memcpy_3);
    tcase_add_test(tc1, memcpy_4);
    tcase_add_test(tc1, memcpy_5);
    tcase_add_test(tc1, memcpy_6);
    tcase_add_test(tc1, memcpy_7);
    tcase_add_test(tc1, memcpy_8);
    tcase_add_test(tc1, memcpy_9);
    tcase_add_test(tc1, memcpy_10);
    tcase_add_test(tc1, memcpy_11);
    tcase_add_test(tc1, memcpy_12);
    tcase_add_test(tc1, memcpy_13);
    tcase_add_test(tc1, memcpy_14);
    tcase_add_test(tc1, memcpy_15);
    tcase_add_test(tc1, memcpy_16);
    tcase_add_test(tc1, memcpy_17);
    tcase_add_test(tc1, memcpy_18);
    tcase_add_test(tc1, memcpy_19);
    tcase_add_test(tc1, memcpy_20);
    suite_add_tcase(s1, tc1);
    return s1;
}