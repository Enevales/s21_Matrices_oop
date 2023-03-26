CC = g++
COVFLAGS = -fprofile-arcs -ftest-coverage
CHECKFLAGS = -Wall -Werror -Wextra -std=c++17
PREF_TEST = ./tests/
UNAME:=$(shell uname -s)
LIB = s21_matrix_oop.a

ifeq ($(UNAME),Linux)
	LDLIBS = -lgtest `pkg-config --cflags --libs check`
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDLIBS = -lgtest
	OPEN_CM=open
endif

all: clean s21_matrix_oop.a test

test: 
	$(CC) s21_matrix_oop.cc $(PREF_TEST)tests_runner.cc $(CPPFLAGS) $(LDLIBS) $(COVFLAGS) #-fsanitize=address
	./a.out

$(LIB): s21_matrix_oop.cc
	ar rcs $(LIB) $^
	ranlib $(LIB)

%.o : %.cc s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report:
	gcov -f  %.cc
	lcov -t "gcov_report" --no-external -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	$(OPEN_CM) ./report/index-sort-f.html


valgrind: test
	valgrind -s --leak-check=full --show-leak-kinds=all  ./a.out

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	find . -name '*.o' -name '*.out' -name '*.exe' -type f -delete
	rm -rf ./report
	find . -name '*.gcno' -type f -delete
	find . -name '*.gcda' -type f -delete
	find . -name '*.info' -type f -delete
	rm -rf test
	rm -rf *.html 
	rm -rf *.css