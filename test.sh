#!/bin/bash
while true; do
  rspec --color ./spec/equation_parser_cpp_spec.rb
  sleep 1
done
