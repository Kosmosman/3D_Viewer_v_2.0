.PHONY: all install dvi dist tests gcov_report leaks valgrind clang clean

CC=gcc
CXXFLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17
LDFLAGS =-lrt -lpthread -lm -lsubunit
LIBS=-lgtest

TEST_FLAGS:=-g#-fsanitize=address -O1 -fno-omit-frame-pointer
GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

SRC=./Model/**/*.cc

TEST_SRC=./test.cc

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
	${CC} $(CXXFLAGS) $(LIBS) $(SRC) $(TEST_SRC) -o unit_test
else
	${CC} $(CXXFLAGS) $(SRC) ${TEST_SRC} -o unit_test $(LIBS) $(LDFLAGS)
endif
	./unit_test

gcov_report: clean
ifeq ($(OS), Darwin)
	${CC} $(CXXFLAGS) $(GCOV_FLAGS) $(LIBS) $(SRC) $(TEST_SRC) -o gcov_report 
else
	${CC} $(CXXFLAGS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -o gcov_report $(LIBS) $(LDFLAGS)
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
	${CC} $(CXXFLAGS) ${TEST_SRC} $(SRC) -o valgrind_test $(LIBS) $(LDFLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cc ./controller/*.h ./Model/*/*.cc ./Model/*/*.h ./view/app/*.cc ./view/app/*.h
	rm .clang-format


	
