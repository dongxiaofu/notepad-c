# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cg/data/code/wheel/c/notepad

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cg/data/code/wheel/c/notepad/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/notepad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/notepad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/notepad.dir/flags.make

CMakeFiles/notepad.dir/main.c.o: CMakeFiles/notepad.dir/flags.make
CMakeFiles/notepad.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cg/data/code/wheel/c/notepad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/notepad.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/notepad.dir/main.c.o   -c /Users/cg/data/code/wheel/c/notepad/main.c

CMakeFiles/notepad.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/notepad.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/cg/data/code/wheel/c/notepad/main.c > CMakeFiles/notepad.dir/main.c.i

CMakeFiles/notepad.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/notepad.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/cg/data/code/wheel/c/notepad/main.c -o CMakeFiles/notepad.dir/main.c.s

# Object files for target notepad
notepad_OBJECTS = \
"CMakeFiles/notepad.dir/main.c.o"

# External object files for target notepad
notepad_EXTERNAL_OBJECTS =

notepad: CMakeFiles/notepad.dir/main.c.o
notepad: CMakeFiles/notepad.dir/build.make
notepad: CMakeFiles/notepad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cg/data/code/wheel/c/notepad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable notepad"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/notepad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/notepad.dir/build: notepad

.PHONY : CMakeFiles/notepad.dir/build

CMakeFiles/notepad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/notepad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/notepad.dir/clean

CMakeFiles/notepad.dir/depend:
	cd /Users/cg/data/code/wheel/c/notepad/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cg/data/code/wheel/c/notepad /Users/cg/data/code/wheel/c/notepad /Users/cg/data/code/wheel/c/notepad/cmake-build-debug /Users/cg/data/code/wheel/c/notepad/cmake-build-debug /Users/cg/data/code/wheel/c/notepad/cmake-build-debug/CMakeFiles/notepad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/notepad.dir/depend

