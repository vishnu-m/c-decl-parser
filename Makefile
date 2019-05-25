INCDIR = $(shell llvm-config --includedir)
LDFLAGS = $(shell llvm-config --ldflags)

all: libclang_parse.bin

libclang_parse.bin: src/main.cpp
	clang++ -std=c++11 -I $(INCDIR) $(LDFLAGS) -lclang -o libclang_parse.bin src/main.cpp

test: libclang_parse.bin
	./libclang_parse.bin src/test.c 7 9 -Wall

clean:
	rm -f libclang_parse.bin
