#!/bin/bash

prog=../libclang_parse
cd `dirname $0`

for file in *.c; do
    out=${file%.c}.out
    tmp=`mktemp /tmp/test.XXXXXX`
    $prog $file -Wall > $tmp
    if ! cmp --silent $tmp $out; then
        echo "test failed: $file"
        exit 1
    fi
    rm $tmp
done