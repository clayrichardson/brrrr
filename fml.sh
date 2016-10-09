#!/bin/bash
set -ex

echo "TURN DOWN FOR WHAT"

source ./install_deps.sh
source ./generate.sh
source ./build.sh
source ./test.sh

echo "looks good, now running with fixtures..."
pushd ./cpp/build
for i in ../../ruby/fixtures/fixture{1..6}.txt; do
  ./EquationParser $i
done
popd
