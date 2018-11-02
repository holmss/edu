#!/bin/bash
#clear old tests
rm tmp
rm -rf tests/
mkdir tests
#compile cheker
echo "Compile cheker"
cd Aho
make
cd ..
#compile generator
echo "Compile generator"
cd Generator
make
rm -rf tests/
mkdir tests
./gen 100000 10
mv tests/*test* ../tests
cd ..
#compile Lab4
echo "Compile Lab"
cd Ajk
make
cd ..

echo "Generate answers"
for test_file in `ls tests/*.t`; do

    if ! ./Aho/Aho < $test_file > "${test_file%.*}.a" ; then
        echo "ERROR"
        continue
    fi 
done

echo "Execute tests"
for test_file in `ls tests/*.t`; do
echo "Execute $test_file"
    if ! ./Ajk/Ajk < $test_file > tmp ; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}"

    if ! diff -u "${answer_file}.a" tmp ; then
        echo "Failed ${test_file%.*}"
    else
        echo "OK"
    fi 
done
echo "All tests executed"
