# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/schre/workspace/src/blueberry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/schre/workspace/src/blueberry/build

# Include any dependencies generated for this target.
include CMakeFiles/ImGui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ImGui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ImGui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ImGui.dir/flags.make

CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o: ../include/imgui/imgui.cpp
CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/schre/workspace/src/blueberry/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o -MF CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o.d -o CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o -c /home/schre/workspace/src/blueberry/include/imgui/imgui.cpp

CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/schre/workspace/src/blueberry/include/imgui/imgui.cpp > CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.i

CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/schre/workspace/src/blueberry/include/imgui/imgui.cpp -o CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.s

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o: ../include/imgui/backends/imgui_impl_glfw.cpp
CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/schre/workspace/src/blueberry/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o -c /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_glfw.cpp

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.i

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.s

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o: ../include/imgui/backends/imgui_impl_opengl3.cpp
CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/schre/workspace/src/blueberry/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o -c /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_opengl3.cpp

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.i

CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/schre/workspace/src/blueberry/include/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.s

# Object files for target ImGui
ImGui_OBJECTS = \
"CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o" \
"CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o" \
"CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o"

# External object files for target ImGui
ImGui_EXTERNAL_OBJECTS =

libImGui.a: CMakeFiles/ImGui.dir/include/imgui/imgui.cpp.o
libImGui.a: CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_glfw.cpp.o
libImGui.a: CMakeFiles/ImGui.dir/include/imgui/backends/imgui_impl_opengl3.cpp.o
libImGui.a: CMakeFiles/ImGui.dir/build.make
libImGui.a: CMakeFiles/ImGui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/schre/workspace/src/blueberry/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libImGui.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ImGui.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImGui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ImGui.dir/build: libImGui.a
.PHONY : CMakeFiles/ImGui.dir/build

CMakeFiles/ImGui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ImGui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ImGui.dir/clean

CMakeFiles/ImGui.dir/depend:
	cd /home/schre/workspace/src/blueberry/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/schre/workspace/src/blueberry /home/schre/workspace/src/blueberry /home/schre/workspace/src/blueberry/build /home/schre/workspace/src/blueberry/build /home/schre/workspace/src/blueberry/build/CMakeFiles/ImGui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ImGui.dir/depend

