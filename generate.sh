#!/bin/bash
set -ex

echo "cleaning ./cpp/build..."
rm -rv ./cpp/build/* || echo "nice and clean :)"

echo "generating cmake pedantry..."
pushd ./cpp/build/
cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -G "Unix Makefiles"
popd
