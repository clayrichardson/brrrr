#!/bin/bash
set -ex

pushd ./ruby
echo "running ruby tests to shrek the ruby code..."
bundle exec rspec --color ./spec/
echo "running ruby tests to shrek the cpp executable ..."
bundle exec rspec --color ./spec/equation_parser_cpp.rb # minus _spec.rb suffix so rspec doesn't automagically do thangs
popd
