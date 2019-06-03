INCDIR = $(shell llvm-config --includedir)
LDFLAGS = $(shell llvm-config --ldflags)

all: libclang_parse.bin

libclang_parse.bin: src/main.c
	clang -I $(INCDIR) $(LDFLAGS) -lclang -o libclang_parse.bin src/main.c -Wall

test: libclang_parse.bin
	./libclang_parse.bin src/test.c 7 9 -Wall

clean:
	rm -f libclang_parse.bin

ast-dump: src/test.c
	clang -Xclang -ast-dump src/test.c
