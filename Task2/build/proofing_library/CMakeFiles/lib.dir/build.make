# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kirill/GitHub/git-repos/MathLogic/Task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kirill/GitHub/git-repos/MathLogic/Task2/build

# Include any dependencies generated for this target.
include proofing_library/CMakeFiles/lib.dir/depend.make

# Include the progress variables for this target.
include proofing_library/CMakeFiles/lib.dir/progress.make

# Include the compile flags for this target's objects.
include proofing_library/CMakeFiles/lib.dir/flags.make

proofing_library/CMakeFiles/lib.dir/checker.cpp.o: proofing_library/CMakeFiles/lib.dir/flags.make
proofing_library/CMakeFiles/lib.dir/checker.cpp.o: ../proofing_library/checker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/GitHub/git-repos/MathLogic/Task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object proofing_library/CMakeFiles/lib.dir/checker.cpp.o"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib.dir/checker.cpp.o -c /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/checker.cpp

proofing_library/CMakeFiles/lib.dir/checker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib.dir/checker.cpp.i"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/checker.cpp > CMakeFiles/lib.dir/checker.cpp.i

proofing_library/CMakeFiles/lib.dir/checker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib.dir/checker.cpp.s"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/checker.cpp -o CMakeFiles/lib.dir/checker.cpp.s

proofing_library/CMakeFiles/lib.dir/checker.cpp.o.requires:

.PHONY : proofing_library/CMakeFiles/lib.dir/checker.cpp.o.requires

proofing_library/CMakeFiles/lib.dir/checker.cpp.o.provides: proofing_library/CMakeFiles/lib.dir/checker.cpp.o.requires
	$(MAKE) -f proofing_library/CMakeFiles/lib.dir/build.make proofing_library/CMakeFiles/lib.dir/checker.cpp.o.provides.build
.PHONY : proofing_library/CMakeFiles/lib.dir/checker.cpp.o.provides

proofing_library/CMakeFiles/lib.dir/checker.cpp.o.provides.build: proofing_library/CMakeFiles/lib.dir/checker.cpp.o


proofing_library/CMakeFiles/lib.dir/parser.cpp.o: proofing_library/CMakeFiles/lib.dir/flags.make
proofing_library/CMakeFiles/lib.dir/parser.cpp.o: ../proofing_library/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/GitHub/git-repos/MathLogic/Task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object proofing_library/CMakeFiles/lib.dir/parser.cpp.o"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib.dir/parser.cpp.o -c /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/parser.cpp

proofing_library/CMakeFiles/lib.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib.dir/parser.cpp.i"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/parser.cpp > CMakeFiles/lib.dir/parser.cpp.i

proofing_library/CMakeFiles/lib.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib.dir/parser.cpp.s"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/parser.cpp -o CMakeFiles/lib.dir/parser.cpp.s

proofing_library/CMakeFiles/lib.dir/parser.cpp.o.requires:

.PHONY : proofing_library/CMakeFiles/lib.dir/parser.cpp.o.requires

proofing_library/CMakeFiles/lib.dir/parser.cpp.o.provides: proofing_library/CMakeFiles/lib.dir/parser.cpp.o.requires
	$(MAKE) -f proofing_library/CMakeFiles/lib.dir/build.make proofing_library/CMakeFiles/lib.dir/parser.cpp.o.provides.build
.PHONY : proofing_library/CMakeFiles/lib.dir/parser.cpp.o.provides

proofing_library/CMakeFiles/lib.dir/parser.cpp.o.provides.build: proofing_library/CMakeFiles/lib.dir/parser.cpp.o


proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o: proofing_library/CMakeFiles/lib.dir/flags.make
proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o: ../proofing_library/string_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/GitHub/git-repos/MathLogic/Task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib.dir/string_handler.cpp.o -c /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/string_handler.cpp

proofing_library/CMakeFiles/lib.dir/string_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib.dir/string_handler.cpp.i"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/string_handler.cpp > CMakeFiles/lib.dir/string_handler.cpp.i

proofing_library/CMakeFiles/lib.dir/string_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib.dir/string_handler.cpp.s"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/string_handler.cpp -o CMakeFiles/lib.dir/string_handler.cpp.s

proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.requires:

.PHONY : proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.requires

proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.provides: proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.requires
	$(MAKE) -f proofing_library/CMakeFiles/lib.dir/build.make proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.provides.build
.PHONY : proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.provides

proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.provides.build: proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o


proofing_library/CMakeFiles/lib.dir/proofer.cpp.o: proofing_library/CMakeFiles/lib.dir/flags.make
proofing_library/CMakeFiles/lib.dir/proofer.cpp.o: ../proofing_library/proofer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kirill/GitHub/git-repos/MathLogic/Task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object proofing_library/CMakeFiles/lib.dir/proofer.cpp.o"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib.dir/proofer.cpp.o -c /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/proofer.cpp

proofing_library/CMakeFiles/lib.dir/proofer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib.dir/proofer.cpp.i"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/proofer.cpp > CMakeFiles/lib.dir/proofer.cpp.i

proofing_library/CMakeFiles/lib.dir/proofer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib.dir/proofer.cpp.s"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library/proofer.cpp -o CMakeFiles/lib.dir/proofer.cpp.s

proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.requires:

.PHONY : proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.requires

proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.provides: proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.requires
	$(MAKE) -f proofing_library/CMakeFiles/lib.dir/build.make proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.provides.build
.PHONY : proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.provides

proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.provides.build: proofing_library/CMakeFiles/lib.dir/proofer.cpp.o


# Object files for target lib
lib_OBJECTS = \
"CMakeFiles/lib.dir/checker.cpp.o" \
"CMakeFiles/lib.dir/parser.cpp.o" \
"CMakeFiles/lib.dir/string_handler.cpp.o" \
"CMakeFiles/lib.dir/proofer.cpp.o"

# External object files for target lib
lib_EXTERNAL_OBJECTS =

proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/checker.cpp.o
proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/parser.cpp.o
proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o
proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/proofer.cpp.o
proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/build.make
proofing_library/liblib.a: proofing_library/CMakeFiles/lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kirill/GitHub/git-repos/MathLogic/Task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library liblib.a"
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && $(CMAKE_COMMAND) -P CMakeFiles/lib.dir/cmake_clean_target.cmake
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proofing_library/CMakeFiles/lib.dir/build: proofing_library/liblib.a

.PHONY : proofing_library/CMakeFiles/lib.dir/build

proofing_library/CMakeFiles/lib.dir/requires: proofing_library/CMakeFiles/lib.dir/checker.cpp.o.requires
proofing_library/CMakeFiles/lib.dir/requires: proofing_library/CMakeFiles/lib.dir/parser.cpp.o.requires
proofing_library/CMakeFiles/lib.dir/requires: proofing_library/CMakeFiles/lib.dir/string_handler.cpp.o.requires
proofing_library/CMakeFiles/lib.dir/requires: proofing_library/CMakeFiles/lib.dir/proofer.cpp.o.requires

.PHONY : proofing_library/CMakeFiles/lib.dir/requires

proofing_library/CMakeFiles/lib.dir/clean:
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library && $(CMAKE_COMMAND) -P CMakeFiles/lib.dir/cmake_clean.cmake
.PHONY : proofing_library/CMakeFiles/lib.dir/clean

proofing_library/CMakeFiles/lib.dir/depend:
	cd /home/kirill/GitHub/git-repos/MathLogic/Task2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kirill/GitHub/git-repos/MathLogic/Task2 /home/kirill/GitHub/git-repos/MathLogic/Task2/proofing_library /home/kirill/GitHub/git-repos/MathLogic/Task2/build /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library /home/kirill/GitHub/git-repos/MathLogic/Task2/build/proofing_library/CMakeFiles/lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proofing_library/CMakeFiles/lib.dir/depend

