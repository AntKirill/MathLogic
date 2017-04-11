# Math logic homework 2

## For checking all tests of directory tests/ :

Make shure that MAIN_PROJECT_SOURCE_FILES in CMakeLists is test_all_main.cpp.
Then go in directory build/ and run test_all.bash.

## For compiling project to check your own proofments :

Ghange MAIN_PROJECT_SOURCE_FILES in CMakeLists to hw2_main.cpp.
Then go in directory build/ and run compile_hw2.bash.
Stay in that directory and write your proofment in file proof.in, after that run Math_logic_HW2. Results will be in file out.txt.

## For testing generation of correct proofment on all correct tests of directory tests/ :

Change MAIN_PROJECT_SOURCE_FILES in CMakeLists to hw2_main.cpp.
Then go in directory build/ and run test_generation.bash.

## Output of program :

If proofment in proof.in is correct then needed proofment will be in out.txt and time of work will be shown on stdout. Otherwise first line with misstake will be in out.txt and on stdout there will be written "ERROR!" and time of work.

