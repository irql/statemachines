CC=g++
CC_OPTS=-std=c++17 -Wall -I../Catch2/single_include
OUT=test.exe

.PHONY: clean test

clean:
	rm *.exe *.obj *.o

all: $(OUT)

$(OUT): *.cpp include/*.hpp include/machine/*.hpp
	$(CC) $(CC_OPTS) -o $(OUT) *.cpp

test: $(OUT)
	./$(OUT)
