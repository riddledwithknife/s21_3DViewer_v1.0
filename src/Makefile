.PHONY: test

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_FLAGS = `pkg-config --cflags --libs check` -lm -lcheck
MODEL_FILES = $(wildcard Model/*.c)
TEST_FILES = $(wildcard Tests/*.c)

all:
	$(MAKE) clean
	$(MAKE) uninstall
	$(MAKE) install

install:
	$(MAKE) uninstall
	mkdir 3DViewer
	cd 3DViewer && cmake -B build "../View/" && make -C build 3DViewer

uninstall:
	rm -rf 3DViewer

launch:
	open 3DViewer/build/3DViewer.app

dvi:
	open documentation.md

dist:
	 tar -cf 3DViewer.tar 3DViewer

test:
	 $(MAKE) clean
	 $(CC) $(CFLAGS) $(TEST_FILES) $(MODEL_FILES) $(TEST_FLAGS) -o ./Tests/test
	 cd Tests && ./test

gcov_report:
	 $(MAKE) clean
	 $(CC) $(CFLAGS) $(TEST_FILES) $(MODEL_FILES) -coverage $(TEST_FLAGS) -o ./Tests/gcovreport
	 cd Tests && ./gcovreport
	 lcov -t "gcovreport" -o gcovreport.info -c -d .
	 genhtml -o Report gcovreport.info
	 @rm -rf *.a *.info *.gcda *.gcno gcovreport

style:
	 clang-format -style=Google -i Model/*.c Model/*.h View/*.cpp View/*.h View/QtGifImage/gifimage/*.cpp View/QtGifImage/gifimage/*.h View/QtGifImage/giflib/*.c View/QtGifImage/gifimage/*.h Tests/*.c Tests/*.h

clean:
	 @rm -rf *.o *.a Report *.gcno *.gcda  *.tar 3DViewer test gcovreport
