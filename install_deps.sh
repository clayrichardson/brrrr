#!/bin/bash
set -ex

echo "installing ruby dependencies..."

pushd ./ruby
gem install bundle
bundle install
popd
