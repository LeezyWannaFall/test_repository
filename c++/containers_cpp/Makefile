GXX = g++
CXXFLAGS =  -Wall -Wextra -std=c++20 -O2

all: test

test_list: 
	g++ -Wall -Wextra -std=c++20 -O2 s21_list_test.cpp -lgtest -lpthread -o test_list
	./test_list

test_array: 
	g++ -Wall -Wextra -std=c++20 -O2 s21_array_test.cpp -lgtest -lpthread -o test_array
	./test_array

clean:
	rm -f *.o test_list test_array

check_style:
	clang-format -n s21_list.cpp s21_list.h s21_list_test.cpp

fix_style:
	clang-format -i s21_list.h s21_list_test.cpp

.PHONY: all clean check_style fix_style test