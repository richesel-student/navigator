CC = g++
CFLAGS=-std=c++17 -Wpedantic -Wall -Werror -Wextra -g
SOURCE_FILES = Graph/*.cc GraphAlgorithms/*.cc
TEST_FILES = Tests/*.cc
GUI_FILES = ConsoleInterface/*.cc
COVFLAGS = --coverage
TFLAGS = -lgtest_main -lgcov -lgtest


all: clean s21_graph.a s21_graph_algorithms.a console

console:
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(GUI_FILES) main.cc -o console
	./console

s21_graph.a:
	$(CC) $(CFLAGS) -c Graph/*
	ar rcs s21_graph.a s21_graph.o
	ranlib s21_graph.a
	rm -rf s21_*o Graph/*.gch

s21_graph_algorithms.a:
	$(CC) $(CFLAGS) -c GraphAlgorithms/*
	ar rcs s21_graph_algorithms.a s21_graphalgorithms.o s21_ACO.o
	ranlib s21_graph_algorithms.a
	rm -rf s21_*o GraphAlgorithms/*.gch

test: 
	$(CC) $(CFLAGS) $(SOURCE_FILES) $(TEST_FILES) -o test $(TFLAGS)
	./test

gcov_report:
	$(CC) $(CFLAGS) $(COVFLAGS) $(SOURCE_FILES) $(TEST_FILES) -L. $(TFLAGS) -o ./htmlreport.out
	./htmlreport.out
	lcov -t "htmlreport" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	clang-format -i main.cc Graph/* GraphAlgorithms/* ConsoleInterface/* Tests/* Containers/* Matrix/*
	cppcheck --enable=all --suppress=negativeContainerIndex --suppress=missingInclude --language=c++ main.cc $(SOURCE_FILES) $(TEST_FILES) $(GUI_FILES)


leakscheck: test
#	leaks --atExit -- ./test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report *.dSYM *.gcov *.gch html console DataFiles/*ToDot.txt

rebuild: all

.PHONY : clean test gcov_report check leakscheck
