#ifndef SRC_HEADERS_UNIT_TEST_H_
#define SRC_HEADERS_UNIT_TEST_H_

#include <check.h>
#include <string.h>

#include "s21_string.h"

//Suite *suite_strlen(void);
//Suite *suite_strspn(void);
//Suite *suite_strcspn(void);
//Suite *suite_memcmp(void);
//Suite *suite_strcmp(void);
//Suite *suite_strncmp(void);
//Suite *suite_memcpy(void);
//Suite *suite_memmove(void);
//Suite *suite_memset(void);
//Suite *suite_strcpy(void);
//Suite *suite_strncpy(void);
//Suite *suite_memchr(void);
//Suite *suite_strrchr(void);
//Suite *suite_strchr(void);
//Suite *suite_strpbrk(void);
//Suite *suite_strstr(void);
//Suite *suite_strtok(void);
//Suite *suite_strerror(void);
//Suite *suite_strcat(void);
//Suite *suite_strncat(void);
//Suite *suite_to_upper(void);
//Suite *suite_to_lower(void);
//Suite *suite_trim(void);
//Suite *suite_insert(void);
Suite *suite_sprintf(void);
void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_HEADERS_UNIT_TEST_H_
