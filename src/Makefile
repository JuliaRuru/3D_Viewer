XX = g++
CFLAG = -Wall -Wextra -Werror  -std=c++17 -g
OS := $(shell uname -s)
TEST_FLAGS = -lgtest -lgtest_main -lpthread
APP = build/s21_3D_Viewer_2_0.app

ifeq ($(OS), Darwin)
XX += -D OS_MAC
else
XX += -D OS_LINUX
endif

default: all

all: clean install test

build: clean
	mkdir build
	cd ./build/ && qmake ../ && make

install: uninstall build
	mkdir $(HOME)/Desktop/3D_Viewer/
	cp -rf $(APP) $(HOME)/Desktop/3D_Viewer/
	make clean

run: uninstall clean install
	open $(HOME)/Desktop/3D_Viewer/$(APP)

uninstall:
	rm -rf $(HOME)/Desktop/3D_Viewer/

dvi:
	makeinfo --html --no-warn --no-validate --force doc.texi
	open ./doc/index.html

dist: clean
	mkdir dist/
	tar -cvf 3D_Viewer_v2.tgz *
	mv 3D_Viewer_v2.tgz dist/

test_prepare: clean
	$(XX) $(CFLAG) test.cpp Model/s21_viewer.cpp Controller/controller.cpp Model/s21_matrix_oop.cpp -lstdc++ $(TEST_FLAGS) -o test

test: test_prepare
	./test

leaks: test_prepare	
	CK_FORK=no leaks --atExit -- ./test

clean:
	rm -rf *.o *.gcda *.gcno *.info *.dSYM test report build doc dist

rebuild: clean all
