CC=gcc
CFLAG=-Wall -Wextra -Werror
APP=build/3D_viewer.app

default: all

all: uninstall clean install test

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	mkdir $(HOME)/Desktop/3D_Viewer/
	cp -rf $(APP) $(HOME)/Desktop/3D_Viewer/
	make clean

run: uninstall clean install
	open $(HOME)/Desktop/3D_Viewer/3D_viewer.app

uninstall:
	rm -rf $(HOME)/Desktop/3D_Viewer/

dvi:
	makeinfo --html --no-warn --no-validate --force doc.texi
	open ./doc/index.html

check: test
	cp -f ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --filter=-runtime/printf --extensions=c *.c
	python3 ../materials/linters/cpplint.py --extensions=h rendering_calculations.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf CPPLINT.cfg
	CK_FORK=no leaks --atExit -- ./test

dist: clean
	mkdir dist/
	tar -cvf 3D_Viewer.tgz *
	mv 3D_Viewer.tgz dist/

rendering_calculations.o:
	$(CC) $(CFLAG) -c rendering_calculations.c -o rendering_calculations.o

test_prepare: clean rendering_calculations.o
	$(CC) $(CFLAG) -c test.c -o test.o
	$(CC) test.o rendering_calculations.o -o test -lcheck

test: test_prepare
	./test

gcov_report: test_prepare
	$(CC) --coverage test.c -o test -lcheck rendering_calculations.c
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o *.gcda *.gcno *.info test report build doc dist

rebuild: clean all
