#!/bin/bash
if [ -f ./cache-test ]
then
  rm cache-test
fi

echo
echo "Provided Cache TESTS: "
echo
make cache-test TEST_CACHE=cache_1c_1e_1k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=cache_65536c_2e_16k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=cache_1048576c_256e_256k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=cache_16384c_4e_4k.o
./cache-test
echo
rm cache-test
make cache-test TEST_CACHE=cache_32768c_8e_8k.o
./cache-test
echo
echo "Mystery 0:"
echo
rm cache-test
make cache-test TEST_CACHE=mystery0.o
./cache-test
echo
echo "Mystery 1:"
echo
rm cache-test
make cache-test TEST_CACHE=mystery1.o
./cache-test
echo
echo "Mystery 2: "
echo
rm cache-test
make cache-test TEST_CACHE=mystery2.o
./cache-test
echo
echo "Mystery 3:"
echo
rm cache-test
make cache-test TEST_CACHE=mystery3.o
./cache-test
echo
echo "Finished."
echo
rm cache-test
