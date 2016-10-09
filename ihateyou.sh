#!/bin/bash
set -ex

echo "(ノಠ益ಠ)ノ彡┻━┻"

source ./generate.sh
source ./build.sh

echo "#notestslol"
echo "running with fixtures..."
pushd ./cpp/build
for i in ../../ruby/fixtures/fixture{1..6}.txt; do
  ./EquationParser $i
done
popd
