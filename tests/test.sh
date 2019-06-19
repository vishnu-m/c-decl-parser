#!/bin/bash

for file in $PWD/*.c; do
    out=${file%.c}.out
    tmp=`mktemp /tmp/test.XXXXXX`
    make curr_file=$file specific_file_out | grep -vE '^make|^./libclang_parse.bin' >> $tmp
    if ! cmp --silent $tmp $out; then
        echo "test failed: $file"
        exit 1
    fi
    rm $tmp
done

echo "Tests successful"

