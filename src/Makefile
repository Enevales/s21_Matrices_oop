CC = g++
COVFLAGS = -fprofile-arcs -ftest-coverage
CHECKFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17
PREF_TEST = ./tests/
UNAME:=$(shell uname -s)
LIB = s21_matrix_oop.a

ifeq ($(UNAME),Linux)
	LDLIBS = -lgtest 
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDLIBS = -lgtest
	OPEN_CM=open
endif

all: clean s21_matrix_oop.a test

test: $(LIB)
	$(CC) $(PREF_TEST)tests_runner.cc $(LDLIBS) -L. $(LIB)
	./a.out

$(LIB): s21_matrix_oop.o
	ar rcs $(LIB) $^
	ranlib $(LIB)

%.o : %.cc s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report:
	$(CC) $(COVFLAGS) s21_matrix_oop.cc $(PREF_TEST)tests_runner.cc -o report.out $(LDLIBS)
	./report.out
	gcov -f  %.cc
	lcov -t "gcov_report" --no-external -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	$(OPEN_CM) ./report/index-sort-f.html


valgrind: test #LINUX only
	valgrind -s --leak-check=full --show-leak-kinds=all  ./a.out

clang:
	cppcheck  *.h *.cc  --language=c++
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i tests/*.cc *cc *.h
	clang-format -n tests/*.cc *.cc *h
	rm -rf .clang-format


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