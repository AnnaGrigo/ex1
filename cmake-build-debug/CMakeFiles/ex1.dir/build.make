﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\user\CLionProjects\RatuvMivne1\ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\ex1.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\ex1.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\ex1.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\ex1.dir\flags.make

CMakeFiles\ex1.dir\main.cpp.obj: CMakeFiles\ex1.dir\flags.make
CMakeFiles\ex1.dir\main.cpp.obj: ..\main.cpp
CMakeFiles\ex1.dir\main.cpp.obj: CMakeFiles\ex1.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex1.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\ex1.dir\main.cpp.obj.d --working-dir=C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\ex1.dir\main.cpp.obj /FdCMakeFiles\ex1.dir\ /FS -c C:\Users\user\CLionProjects\RatuvMivne1\ex1\main.cpp
<<

CMakeFiles\ex1.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe > CMakeFiles\ex1.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\user\CLionProjects\RatuvMivne1\ex1\main.cpp
<<

CMakeFiles\ex1.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ex1.dir\main.cpp.s /c C:\Users\user\CLionProjects\RatuvMivne1\ex1\main.cpp
<<

CMakeFiles\ex1.dir\TreeTester.cpp.obj: CMakeFiles\ex1.dir\flags.make
CMakeFiles\ex1.dir\TreeTester.cpp.obj: ..\TreeTester.cpp
CMakeFiles\ex1.dir\TreeTester.cpp.obj: CMakeFiles\ex1.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex1.dir/TreeTester.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\ex1.dir\TreeTester.cpp.obj.d --working-dir=C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\ex1.dir\TreeTester.cpp.obj /FdCMakeFiles\ex1.dir\ /FS -c C:\Users\user\CLionProjects\RatuvMivne1\ex1\TreeTester.cpp
<<

CMakeFiles\ex1.dir\TreeTester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/TreeTester.cpp.i"
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe > CMakeFiles\ex1.dir\TreeTester.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\user\CLionProjects\RatuvMivne1\ex1\TreeTester.cpp
<<

CMakeFiles\ex1.dir\TreeTester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/TreeTester.cpp.s"
	C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ex1.dir\TreeTester.cpp.s /c C:\Users\user\CLionProjects\RatuvMivne1\ex1\TreeTester.cpp
<<

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles\ex1.dir\main.cpp.obj" \
"CMakeFiles\ex1.dir\TreeTester.cpp.obj"

# External object files for target ex1
ex1_EXTERNAL_OBJECTS =

ex1.exe: CMakeFiles\ex1.dir\main.cpp.obj
ex1.exe: CMakeFiles\ex1.dir\TreeTester.cpp.obj
ex1.exe: CMakeFiles\ex1.dir\build.make
ex1.exe: CMakeFiles\ex1.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ex1.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ex1.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2022\BUILDT~1\VC\Tools\MSVC\1432~1.313\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\ex1.dir\objects1.rsp @<<
 /out:ex1.exe /implib:ex1.lib /pdb:C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug\ex1.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\ex1.dir\build: ex1.exe
.PHONY : CMakeFiles\ex1.dir\build

CMakeFiles\ex1.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex1.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ex1.dir\clean

CMakeFiles\ex1.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\user\CLionProjects\RatuvMivne1\ex1 C:\Users\user\CLionProjects\RatuvMivne1\ex1 C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug C:\Users\user\CLionProjects\RatuvMivne1\ex1\cmake-build-debug\CMakeFiles\ex1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\ex1.dir\depend

