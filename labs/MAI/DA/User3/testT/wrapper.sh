#!/bin/bash
make
make clear

 rm -rf tests
 mkdir -p tests
 if ! python3 test_generator.py ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
 fi

for test_file in `ls tests/*.t`; do
    echo "Execute ${test_file}"
    if ! ./BRTree < $test_file > tmp ; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" tmp ; then
        echo "Failed"
    else
        echo "OK"
    fi 
done
