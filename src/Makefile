.PHONY: all install dvi dist tests gcov_report leaks valgrind clang clean

CC=g++
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
TEST_FLAGS:=$(CFLAGS) -g#-fsanitize=address -O1 -fno-omit-frame-pointer
LINUX_FLAGS =-lrt -lpthread -lm -lsubunit
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
LIBS=-lgtest
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

PREF_SRC=./Model/parcer
SRC=$(wildcard $(PREF_SRC)/*.cc)

# SRC=./model/model.cc

# PREF_LIB_SRC=./model/common
# LIB_SRC=$(wildcard $(PREF_LIB_SRC)/*.c)

# PREF_TEST_SRC=./model/tests
# TEST_SRC=$(wildcard $(PREF_TEST_SRC)/*.c)

TEST_SRC=./Model/test/test.cc

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: tests gcov_report install dist dvi open

install: clean uninstall
	mkdir -p build && cd build && qmake ..
	cd build && make && make clean && rm Makefile

uninstall:
	rm -rf build*
	rm -rf ../build*
	rm -rf ./view/build*

dvi:
	$(OPEN_CMD) readme.html

dist: clean
	zip -r 3DViewer_v2.0.zip *

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) $(SRC) $(TEST_SRC) -o unit_test
else
	${CC} $(TEST_FLAGS) $(SRC) ${TEST_SRC} $(CPPFLAGS) -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS) $(CPPFLAGS) $(SRC) $(TEST_SRC) -o gcov_report 
else
	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -o gcov_report $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
endif
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html


clean:
	rm -rf *.dSYM
	rm -rf unit_test
	rm -rf *.gcda	*.gcno *.info report gcov_report
	rm -rf valgrind_test RESULT_VALGRIND.txt
	rm -rf *.zip

open:
ifeq ($(OS), Darwin)
	./build/3DViewer.app/Contents/MacOS/3DViewer
else
	./build/3DViewer
endif

leaks: tests
	leaks -atExit -- ./unit_test

valgrind: clean
	${CC} $(TEST_FLAGS) ${TEST_SRC} $(SRC) $(CPPFLAGS) -o valgrind_test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cc ./controller/*.cc ./controller/*.h ./Model/*/*.cc ./Model/*/*.h ./view/app/*.cc ./view/app/*.h
	rm .clang-format


	
