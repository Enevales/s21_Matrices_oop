CC = g++
CPPFLAGS = -lgtest -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
PREF_SRC = ./lib/
PREF_TEST = ./tests/

all: clean tests #s21_matrix_oop.a

test: 
	$(CC) s21_matrix_oop.cpp $(PREF_TEST)tests_runner.cpp $(CPPFLAGS) $(CHECKFLAGS)
	./a.exe
clean:
	rm *.exe