CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TESTFLAGS = -lgtest -lgmock -pthread
TESTFUNC = calcModel.cc calcController.cc creditModel.cc creditController.cc depositModel.cc depositController.cc
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
#-lsubunit
	CHECKFLAGS=-lpthread -lrt -lm -lsubunit
	LCOVFLAGS =
else
	CHECKFLAGS= -lm -lpthread
	LCOVFLAGS = --ignore-errors mismatch
endif

all: clean install dist dvi gcov_report check_style leaks clean

rebuild: clean all

install: uninstall
	mkdir build
	cp -rf calculator_cc.pro build
	cp -rf *.cc build
	cp -rf *.h build
	cp -rf *.ui build
	cd build && qmake6 calculator_cc.pro
	make -C build
	cd build && make clean
	open ./build/calculator_cc.app/Contents/MacOS/calculator_cc

uninstall:
	rm -rf build
	make clean

dvi:
	open ./readme.txt

dist:
	tar -cvf build/calculator_cc.tar build
	gzip build/calculator_cc.tar
	mv build/calculator_cc.tar.gz ./

test: 
	$(CC) $(CFLAGS) test.cc $(TESTFUNC) -o test $(TESTFLAGS)
	./test

test_obj:
	$(CC) $(CFLAGS) test.cc $(TESTFUNC) -c $(TESTFLAGS)

gcov_report: test_obj
	$(CC) $(GCOVFLAGS) $(CFLAGS) test.o $(TESTFUNC) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -o test.info --no-external -c -d . $(LCOVFLAGS)
	genhtml -o report test.info
	rm -rf gcovreport gcovreport.info *.gcda *.gcno string_test.gcda string_test.gcno
	open report/index.html

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cc
	clang-format -i *.h
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc >> logfile.log
	clang-format -n *.h >> logfile.log
	rm -rf .clang-format

valgrind:
	$(CC) $(CFLAGS) test.cc $(TESTFUNC) -o test $(TESTFLAGS)
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

leaks: test
	CK_FORK=no leaks --atExit -- ./test >> leaksfile.log #leaks --atExit --
	
clean:
	rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
		*.log \
		.qmake.stash
