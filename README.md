
  

# c-decl-parser

  

A Lua library to parse C header files. The library generates a Lua representation of the static C declarations.

  

# Prerequisite

  

- Clang 8

  

# Installation

  

**Installing Clang in Ubuntu :**

1. Install a few prerequisites for running Clang

> sudo apt install build-essential xz-utils curl

  

2. Download and extract Clang 8.0.0

  

> curl -SL http://releases.llvm.org/8.0.0/clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz | tar -xJC .

> mv clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz clang_8.0.0

> sudo mv clang_8.0.0 /usr/local

  

3. Add Clang to your system PATH

  

> export PATH=/usr/local/clang_8.0.0/bin:$PATH

  

> export LD_LIBRARY_PATH=/usr/local/clang_8.0.0/lib:$LD_LIBRARY_PATH

  

**Setting up :** 

  

1. Print out AST representation of declarations in `test.c`

> make test

  

2. Print out Clang's full featured AST representation of `test.c`

  

> make ast-dump