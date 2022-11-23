
CC = gcc
FLAG_C = -c
FLAG_O = -o
# ASAN = -fsanitize=address
FLAG_COV = --coverage 
FLAG_ER = -Wall -Werror -Wextra -std=c11
s21_STRING_C = s21_strlen.c 
s21_STRING_O = s21_strlen.o
SUITE_CASES_C = suite_*.c
SUITE_CASES_O = suite_*.o

all: clean s21_string.a test gcov_report
# --- СОЗДАНИЕ БИБЛИОТЕКИ ФУНКЦИЙ ---

s21_string.a:
	gcc -c -Wall -Werror -Wextra -std=c11 s21_strlen.c s21_strcat.c
	ar rc s21_string.a s21_strlen.o s21_strcat.o
	ranlib s21_string.a

test : s21_string.a
	gcc -c -Wall -Werror -Wextra test_s21_strlen.c test_s21_strcat.c all_tests_run.c
	ar rc suite_cases.a test_s21_strlen.o test_s21_strcat.o
	ranlib suite_cases.a
	gcc -Wall -Werror -Wextra --coverage -o tests s21_string.a suite_cases.a s21_strlen.c s21_strcat.c all_tests_run.o -lcheck
	./tests
gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details -o report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +