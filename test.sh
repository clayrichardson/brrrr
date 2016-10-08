#!/bin/bash
while true; do
  rspec --color ./spec/equation_parser_cpp.rb # minus _spec.rb suffix so rspec doesn't automagically do thangs
  sleep 1
done
