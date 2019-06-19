#!/bin/bash

for file in $PWD/*.c; do
    out=${file%.c}.out
    make curr_file=$file specific_file_out | grep -vE '^make|^./libclang_parse.bin' >> $out
done