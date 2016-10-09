# About
I learned minimal C++ in college before I dropped out, and haven't really touched it until recently for my `Kinectv2 => openni2 => PCL => 3Dmesh => ML => industrial robot` project. I forgot how stupid the compiler makes you feel.

It was easier to sketch this in Ruby with tests to get the correct logic and modularity, then port to C++ since I'm unfamiliar with C++ unit testing frametwerks. This is a benefit, as the documentation for the logic is coded into the tests. There are also ruby integration tests for the CPP executable :D

I was good to go with 5 fixtures, but I decided to add a more crazy 6th fixture zomg! This uncovered a bug where I would update `std::map left_hash["crazy"]` with an `int` and this would cause the value to be null upon future lookups. Wrapping the map in a accessor method convinced the compiler to pay attention.

I'm not sure why this did not cause a compiler error or runtime error at that specific line, since the type is `map<string, string>`. Instead, it caused a segfault from all the recursions. `(╯ಥ╭╮ರೃ)╯︵ ┻━┻ `

# Optimizations
Prolly an AST or something like that. Passing all these strings around might not help with performance, but it makes the code easier to reason about.

# Requirements
1. GNU bash, version 3.2.57(1)-release (x86_64-apple-darwin14)
1. ruby 2.3.0p0 (2015-12-25 revision 53290) [x86_64-darwin14]
  * This is for the unit and integration tests
1. buncha gems (this is installed with the `install_deps.sh` script)
1. RVM, chruby or some other way of keeping your system ruby unmucked. Or not. `#YOLO`
1. cmake 3.6.1

# Building
Once you have ruby-2.3.0 and a gemset to isolate your system ruby, just run:

```
./fml.sh
```

If you want to turn down and skip all the cool ruby stuff, just run:

```
./ihateyou.sh
```

# Output
You should see something like:

```
herpderp:tesla clayrichardson$ ./fml.sh
+ echo 'TURN DOWN FOR WHAT'
TURN DOWN FOR WHAT
+ source ./install_deps.sh
++ set -ex
++ echo 'installing ruby dependencies...'
installing ruby dependencies...
++ pushd ./ruby
~/twerkspace/tesla/ruby ~/twerkspace/tesla
++ gem install bundle
Successfully installed bundle-0.0.1
Parsing documentation for bundle-0.0.1
Done installing documentation for bundle after 0 seconds
1 gem installed
++ bundle install
Using byebug 9.0.6
Using coderay 1.1.1
Using contracts 0.14.0
Using did_you_mean 1.0.2
Using diff-lcs 1.2.5
Using ffi 1.9.14
Using formatador 0.2.5
Using rb-fsevent 0.9.7
Using ruby_dep 1.3.1
Using lumberjack 1.0.10
Using nenv 0.3.0
Using shellany 0.0.1
Using method_source 0.8.2
Using slop 3.6.0
Using thor 0.19.1
Using guard-compat 1.2.1
Using rspec-support 3.5.0
Using bundler 1.13.2
Using rb-inotify 0.9.7
Using notiffany 0.1.0
Using pry 0.10.4
Using rspec-core 3.5.1
Using rspec-expectations 3.5.0
Using rspec-mocks 3.5.0
Using listen 3.1.5
Using pry-byebug 3.4.0
Using rspec 3.5.0
Using guard 2.14.0
Using guard-rspec 4.7.2
Bundle complete! 4 Gemfile dependencies, 29 gems now installed.
Use `bundle show [gemname]` to see where a bundled gem is installed.
++ popd
~/twerkspace/tesla
+ source ./generate.sh
++ set -ex
++ echo 'cleaning ./cpp/build...'
cleaning ./cpp/build...
++ rm -rv './cpp/build/*'
rm: ./cpp/build/*: No such file or directory
++ echo 'nice and clean :)'
nice and clean :)
++ echo 'generating cmake pedantry...'
generating cmake pedantry...
++ pushd ./cpp/build/
~/twerkspace/tesla/cpp/build ~/twerkspace/tesla
++ cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -G 'Unix Makefiles'
-- The C compiler identification is AppleClang 7.0.2.7000181
-- The CXX compiler identification is AppleClang 7.0.2.7000181
-- Check for working C compiler: /usr/bin/gcc
-- Check for working C compiler: /usr/bin/gcc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/g++
-- Check for working CXX compiler: /usr/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/clayrichardson/twerkspace/tesla/cpp/build
++ popd
~/twerkspace/tesla
+ source ./build.sh
++ set -ex
++ echo 'building cpp files...'
building cpp files...
++ pushd ./cpp/build
~/twerkspace/tesla/cpp/build ~/twerkspace/tesla
++ make clean
++ make
Scanning dependencies of target EquationParser
[ 33%] Building CXX object CMakeFiles/EquationParser.dir/src/main.cpp.o
[ 66%] Building CXX object CMakeFiles/EquationParser.dir/src/equationparser.cpp.o
[100%] Linking CXX executable EquationParser
[100%] Built target EquationParser
++ popd
~/twerkspace/tesla
+ source ./test.sh
++ set -ex
++ pushd ./ruby
~/twerkspace/tesla/ruby ~/twerkspace/tesla
++ echo 'running ruby tests to shrek the ruby code...'
running ruby tests to shrek the ruby code...
++ bundle exec rspec --color ./spec/

EquationParser
  #initialize
    parses the data into a dictionary
  #split_on
    with equal
      finds the left-hand side of the equation
    with plus sign
      creates an array of operands
  #evaluate
    with simple input
      does the math
    with some variables
      does the math
    with the sample input
      does the math
    with the crazy input
      does the math
  #is_integer
    with strings
      returns true if integer
      returns false if string
  #contains_operator
    returns true if string contains operator
    returns false if string does not contain operator
  #resolve_variable
    returns the value of the variable
  #compute
    with 1 level of resolution
      resolves and computes the value of the string
    with 2 levels of resolution
      resolves and computes the value of the string
    with 3 levels of resolution
      resolves and computes the value of the string

Finished in 0.00963 seconds (files took 0.26838 seconds to load)
15 examples, 0 failures

++ echo 'running ruby tests to shrek the cpp executable ...'
running ruby tests to shrek the cpp executable ...
++ bundle exec rspec --color ./spec/equation_parser_cpp.rb

EquationParser
  the cpp cli
    returns an error if no filename is given
running command: ../cpp/EquationParser ./fixtures/not_a_file.txt
    returns an error if no data was read from file
running command: ../cpp/EquationParser ./fixtures/fixture1.txt
    does the math with simple input
running command: ../cpp/EquationParser ./fixtures/fixture2.txt
    does the math with some variables
running command: ../cpp/EquationParser ./fixtures/fixture5.txt
    does the math with the sample input
running command: ../cpp/EquationParser ./fixtures/fixture6.txt
    does the math with the crazy input

Finished in 0.02851 seconds (files took 0.254 seconds to load)
6 examples, 0 failures

++ popd
~/twerkspace/tesla
+ echo 'looks good, now running with fixtures...'
looks good, now running with fixtures...
+ pushd ./cpp/build
~/twerkspace/tesla/cpp/build ~/twerkspace/tesla
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture1.txt
answer1 = 2
answer2 = 4
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture2.txt
answer1 = 5
answer2 = 4
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture3.txt
answer1 = 7
answer2 = 6
answer3 = 4
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture4.txt
answer1 = 9
answer2 = 8
answer3 = 6
answer4 = 4
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture5.txt
location = 16
offset = 7
origin = 8
random = 2
+ for i in '../../ruby/fixtures/fixture{1..6}.txt'
+ ./EquationParser ../../ruby/fixtures/fixture6.txt
bacon = 285
crazy = 303
it = 35
items = 180
keep = 45
location = 319
offset = 7
origin = 8
random = 2
stuff = 35
things = 35
+ popd
~/twerkspace/tesla
```

# Citations

`http://stackoverflow.com/`
