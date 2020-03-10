CC=g++
CC_OPTS=-std=c++17
OUT=test.exe

.PHONY: clean test

clean:
	rm *.exe *.obj *.o

all: $(OUT)

$(OUT): *.cpp include/*.hpp
	$(CC) $(CC_OPTS) -o $(OUT) *.cpp

test: $(OUT)
	./$(OUT)
