# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2017.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2017.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\work\itmo\da\lab_ks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\work\itmo\da\lab_ks\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/template.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template.dir/flags.make

CMakeFiles/template.dir/main.cpp.obj: CMakeFiles/template.dir/flags.make
CMakeFiles/template.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\work\itmo\da\lab_ks\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/template.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\template.dir\main.cpp.obj -c C:\work\itmo\da\lab_ks\main.cpp

CMakeFiles/template.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\work\itmo\da\lab_ks\main.cpp > CMakeFiles\template.dir\main.cpp.i

CMakeFiles/template.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\work\itmo\da\lab_ks\main.cpp -o CMakeFiles\template.dir\main.cpp.s

CMakeFiles/template.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/template.dir/main.cpp.obj.requires

CMakeFiles/template.dir/main.cpp.obj.provides: CMakeFiles/template.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\template.dir\build.make CMakeFiles/template.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/template.dir/main.cpp.obj.provides

CMakeFiles/template.dir/main.cpp.obj.provides.build: CMakeFiles/template.dir/main.cpp.obj


# Object files for target template
template_OBJECTS = \
"CMakeFiles/template.dir/main.cpp.obj"

# External object files for target template
template_EXTERNAL_OBJECTS =

template.exe: CMakeFiles/template.dir/main.cpp.obj
template.exe: CMakeFiles/template.dir/build.make
template.exe: CMakeFiles/template.dir/linklibs.rsp
template.exe: CMakeFiles/template.dir/objects1.rsp
template.exe: CMakeFiles/template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\work\itmo\da\lab_ks\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable template.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\template.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template.dir/build: template.exe

.PHONY : CMakeFiles/template.dir/build

CMakeFiles/template.dir/requires: CMakeFiles/template.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/template.dir/requires

CMakeFiles/template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\template.dir\cmake_clean.cmake
.PHONY : CMakeFiles/template.dir/clean

CMakeFiles/template.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\work\itmo\da\lab_ks C:\work\itmo\da\lab_ks C:\work\itmo\da\lab_ks\cmake-build-debug C:\work\itmo\da\lab_ks\cmake-build-debug C:\work\itmo\da\lab_ks\cmake-build-debug\CMakeFiles\template.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/template.dir/depend

