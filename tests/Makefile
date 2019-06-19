INCDIR = $(shell llvm-config --includedir)
LDFLAGS = $(shell llvm-config --ldflags)

#Generate .out files which contain the expected output
generate_out: *.c
	bash generate_out.sh 

#Generate .out for specific file specified by curr_file
specific_file_out: libclang_parse.bin
	./libclang_parse.bin $(curr_file) -Wall

libclang_parse.bin: ../src/main.c
	clang -I $(INCDIR) $(LDFLAGS) -lclang -o libclang_parse.bin ../src/main.c -Wall

#Run the test
test: *.c *.out
	bash test.sh

