
CC = gcc
FLAG_C = -c
FLAG_O = -o
# ASAN = -fsanitize=address
FLAG_COV = --coverage 
FLAG_ER = -Wall -Werror -Wextra -std=c11
s21_STRING_C = s21_*.c 
s21_STRING_O = s21_*.o
TEST_CASES_C = test_*.c
TEST_CASES_O = test_*.o

all: clean s21_string.a test gcov_report
# --- СОЗДАНИЕ БИБЛИОТЕКИ ФУНКЦИЙ ---

s21_string.a:
	gcc $(FLAG_C) $(FLAG_ER) $(s21_STRING_C) 
	ar rc s21_string.a $(s21_STRING_O) 
	ranlib s21_string.a

test : s21_string.a
	$(CC) $(FLAG_C) $(FLAG_ER) $(TEST_CASES_C) all_tests_run.c
	ar rc test_cases.a $(TEST_CASES_O)
	ranlib test_cases.a
	gcc -Wall -Werror -Wextra $(FLAG_COV) $(FLAG_O) tests s21_string.a test_cases.a $(s21_STRING_C) all_tests_run.o -lcheck
	./tests
gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details $(FLAG_O) report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +