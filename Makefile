INCDIR = $(shell llvm-config --includedir)
LDFLAGS = $(shell llvm-config --ldflags)

all: libclang_parse

libclang_parse: src/main.c
	clang -I $(INCDIR) $(LDFLAGS) -lclang -o libclang_parse src/main.c -Wall

#Run test script

test: libclang_parse
	bash tests/test.sh

clean:
	rm -f libclang_parse

#for quick verification of program on input given by test.c

ast-dump: src/test.c
	clang -Xclang -ast-dump src/test.c

check: libclang_parse
	./libclang_parse src/test.c -Wall