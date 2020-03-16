CC=g++
CC_OPTS=-std=c++17 -Wall -I../Catch2/single_include
TEST_OUT=test.exe

.PHONY: clean test

clean:
	rm *.exe *.obj *.o *.stackdump

test.o: test.cpp
	$(CC) $(CC_OPTS) -c -o test.o test.cpp

$(TEST_OUT): test.o test_*.cpp include/*.hpp include/machine/*.hpp
	$(CC) $(CC_OPTS) -o $(TEST_OUT) test_*.cpp test.o

test: $(TEST_OUT)
	./$(TEST_OUT)
