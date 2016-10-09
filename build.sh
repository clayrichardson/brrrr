#!/bin/bash
set -ex

echo "building cpp files..."
pushd ./cpp/build
make clean
make
popd
