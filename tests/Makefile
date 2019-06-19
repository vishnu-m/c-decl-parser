INCDIR = $(shell llvm-config --includedir)
LDFLAGS = $(shell llvm-config --ldflags)

generate_out: *.c
	bash generate_out.sh 

specific_file_out: libclang_parse.bin
	./libclang_parse.bin $(curr_file) -Wall

libclang_parse.bin: ../src/main.c
	clang -I $(INCDIR) $(LDFLAGS) -lclang -o libclang_parse.bin ../src/main.c -Wall

test: *.c *.out
	bash test.sh

