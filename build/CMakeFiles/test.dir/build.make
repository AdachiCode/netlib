# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/spanoc/netlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/spanoc/netlib/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/src/base/async_logging.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/async_logging.cc.o: /home/spanoc/netlib/src/base/async_logging.cc
CMakeFiles/test.dir/src/base/async_logging.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/src/base/async_logging.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/async_logging.cc.o -MF CMakeFiles/test.dir/src/base/async_logging.cc.o.d -o CMakeFiles/test.dir/src/base/async_logging.cc.o -c /home/spanoc/netlib/src/base/async_logging.cc

CMakeFiles/test.dir/src/base/async_logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/async_logging.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/async_logging.cc > CMakeFiles/test.dir/src/base/async_logging.cc.i

CMakeFiles/test.dir/src/base/async_logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/async_logging.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/async_logging.cc -o CMakeFiles/test.dir/src/base/async_logging.cc.s

CMakeFiles/test.dir/src/base/current_thread.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/current_thread.cc.o: /home/spanoc/netlib/src/base/current_thread.cc
CMakeFiles/test.dir/src/base/current_thread.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/src/base/current_thread.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/current_thread.cc.o -MF CMakeFiles/test.dir/src/base/current_thread.cc.o.d -o CMakeFiles/test.dir/src/base/current_thread.cc.o -c /home/spanoc/netlib/src/base/current_thread.cc

CMakeFiles/test.dir/src/base/current_thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/current_thread.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/current_thread.cc > CMakeFiles/test.dir/src/base/current_thread.cc.i

CMakeFiles/test.dir/src/base/current_thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/current_thread.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/current_thread.cc -o CMakeFiles/test.dir/src/base/current_thread.cc.s

CMakeFiles/test.dir/src/base/file_util.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/file_util.cc.o: /home/spanoc/netlib/src/base/file_util.cc
CMakeFiles/test.dir/src/base/file_util.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/src/base/file_util.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/file_util.cc.o -MF CMakeFiles/test.dir/src/base/file_util.cc.o.d -o CMakeFiles/test.dir/src/base/file_util.cc.o -c /home/spanoc/netlib/src/base/file_util.cc

CMakeFiles/test.dir/src/base/file_util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/file_util.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/file_util.cc > CMakeFiles/test.dir/src/base/file_util.cc.i

CMakeFiles/test.dir/src/base/file_util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/file_util.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/file_util.cc -o CMakeFiles/test.dir/src/base/file_util.cc.s

CMakeFiles/test.dir/src/base/logfile.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/logfile.cc.o: /home/spanoc/netlib/src/base/logfile.cc
CMakeFiles/test.dir/src/base/logfile.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test.dir/src/base/logfile.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/logfile.cc.o -MF CMakeFiles/test.dir/src/base/logfile.cc.o.d -o CMakeFiles/test.dir/src/base/logfile.cc.o -c /home/spanoc/netlib/src/base/logfile.cc

CMakeFiles/test.dir/src/base/logfile.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/logfile.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/logfile.cc > CMakeFiles/test.dir/src/base/logfile.cc.i

CMakeFiles/test.dir/src/base/logfile.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/logfile.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/logfile.cc -o CMakeFiles/test.dir/src/base/logfile.cc.s

CMakeFiles/test.dir/src/base/logger.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/logger.cc.o: /home/spanoc/netlib/src/base/logger.cc
CMakeFiles/test.dir/src/base/logger.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test.dir/src/base/logger.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/logger.cc.o -MF CMakeFiles/test.dir/src/base/logger.cc.o.d -o CMakeFiles/test.dir/src/base/logger.cc.o -c /home/spanoc/netlib/src/base/logger.cc

CMakeFiles/test.dir/src/base/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/logger.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/logger.cc > CMakeFiles/test.dir/src/base/logger.cc.i

CMakeFiles/test.dir/src/base/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/logger.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/logger.cc -o CMakeFiles/test.dir/src/base/logger.cc.s

CMakeFiles/test.dir/src/base/logstream.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/logstream.cc.o: /home/spanoc/netlib/src/base/logstream.cc
CMakeFiles/test.dir/src/base/logstream.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test.dir/src/base/logstream.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/logstream.cc.o -MF CMakeFiles/test.dir/src/base/logstream.cc.o.d -o CMakeFiles/test.dir/src/base/logstream.cc.o -c /home/spanoc/netlib/src/base/logstream.cc

CMakeFiles/test.dir/src/base/logstream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/logstream.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/logstream.cc > CMakeFiles/test.dir/src/base/logstream.cc.i

CMakeFiles/test.dir/src/base/logstream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/logstream.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/logstream.cc -o CMakeFiles/test.dir/src/base/logstream.cc.s

CMakeFiles/test.dir/src/base/thread.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/thread.cc.o: /home/spanoc/netlib/src/base/thread.cc
CMakeFiles/test.dir/src/base/thread.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test.dir/src/base/thread.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/thread.cc.o -MF CMakeFiles/test.dir/src/base/thread.cc.o.d -o CMakeFiles/test.dir/src/base/thread.cc.o -c /home/spanoc/netlib/src/base/thread.cc

CMakeFiles/test.dir/src/base/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/thread.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/thread.cc > CMakeFiles/test.dir/src/base/thread.cc.i

CMakeFiles/test.dir/src/base/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/thread.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/thread.cc -o CMakeFiles/test.dir/src/base/thread.cc.s

CMakeFiles/test.dir/src/base/timestamp.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/base/timestamp.cc.o: /home/spanoc/netlib/src/base/timestamp.cc
CMakeFiles/test.dir/src/base/timestamp.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test.dir/src/base/timestamp.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/base/timestamp.cc.o -MF CMakeFiles/test.dir/src/base/timestamp.cc.o.d -o CMakeFiles/test.dir/src/base/timestamp.cc.o -c /home/spanoc/netlib/src/base/timestamp.cc

CMakeFiles/test.dir/src/base/timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/base/timestamp.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/base/timestamp.cc > CMakeFiles/test.dir/src/base/timestamp.cc.i

CMakeFiles/test.dir/src/base/timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/base/timestamp.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/base/timestamp.cc -o CMakeFiles/test.dir/src/base/timestamp.cc.s

CMakeFiles/test.dir/src/net/acceptor.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/acceptor.cc.o: /home/spanoc/netlib/src/net/acceptor.cc
CMakeFiles/test.dir/src/net/acceptor.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/test.dir/src/net/acceptor.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/acceptor.cc.o -MF CMakeFiles/test.dir/src/net/acceptor.cc.o.d -o CMakeFiles/test.dir/src/net/acceptor.cc.o -c /home/spanoc/netlib/src/net/acceptor.cc

CMakeFiles/test.dir/src/net/acceptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/acceptor.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/acceptor.cc > CMakeFiles/test.dir/src/net/acceptor.cc.i

CMakeFiles/test.dir/src/net/acceptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/acceptor.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/acceptor.cc -o CMakeFiles/test.dir/src/net/acceptor.cc.s

CMakeFiles/test.dir/src/net/buffer.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/buffer.cc.o: /home/spanoc/netlib/src/net/buffer.cc
CMakeFiles/test.dir/src/net/buffer.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/test.dir/src/net/buffer.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/buffer.cc.o -MF CMakeFiles/test.dir/src/net/buffer.cc.o.d -o CMakeFiles/test.dir/src/net/buffer.cc.o -c /home/spanoc/netlib/src/net/buffer.cc

CMakeFiles/test.dir/src/net/buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/buffer.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/buffer.cc > CMakeFiles/test.dir/src/net/buffer.cc.i

CMakeFiles/test.dir/src/net/buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/buffer.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/buffer.cc -o CMakeFiles/test.dir/src/net/buffer.cc.s

CMakeFiles/test.dir/src/net/channel.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/channel.cc.o: /home/spanoc/netlib/src/net/channel.cc
CMakeFiles/test.dir/src/net/channel.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/test.dir/src/net/channel.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/channel.cc.o -MF CMakeFiles/test.dir/src/net/channel.cc.o.d -o CMakeFiles/test.dir/src/net/channel.cc.o -c /home/spanoc/netlib/src/net/channel.cc

CMakeFiles/test.dir/src/net/channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/channel.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/channel.cc > CMakeFiles/test.dir/src/net/channel.cc.i

CMakeFiles/test.dir/src/net/channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/channel.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/channel.cc -o CMakeFiles/test.dir/src/net/channel.cc.s

CMakeFiles/test.dir/src/net/epoller.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/epoller.cc.o: /home/spanoc/netlib/src/net/epoller.cc
CMakeFiles/test.dir/src/net/epoller.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/test.dir/src/net/epoller.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/epoller.cc.o -MF CMakeFiles/test.dir/src/net/epoller.cc.o.d -o CMakeFiles/test.dir/src/net/epoller.cc.o -c /home/spanoc/netlib/src/net/epoller.cc

CMakeFiles/test.dir/src/net/epoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/epoller.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/epoller.cc > CMakeFiles/test.dir/src/net/epoller.cc.i

CMakeFiles/test.dir/src/net/epoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/epoller.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/epoller.cc -o CMakeFiles/test.dir/src/net/epoller.cc.s

CMakeFiles/test.dir/src/net/event_loop.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/event_loop.cc.o: /home/spanoc/netlib/src/net/event_loop.cc
CMakeFiles/test.dir/src/net/event_loop.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/test.dir/src/net/event_loop.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/event_loop.cc.o -MF CMakeFiles/test.dir/src/net/event_loop.cc.o.d -o CMakeFiles/test.dir/src/net/event_loop.cc.o -c /home/spanoc/netlib/src/net/event_loop.cc

CMakeFiles/test.dir/src/net/event_loop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/event_loop.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/event_loop.cc > CMakeFiles/test.dir/src/net/event_loop.cc.i

CMakeFiles/test.dir/src/net/event_loop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/event_loop.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/event_loop.cc -o CMakeFiles/test.dir/src/net/event_loop.cc.s

CMakeFiles/test.dir/src/net/event_loop_thread.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/event_loop_thread.cc.o: /home/spanoc/netlib/src/net/event_loop_thread.cc
CMakeFiles/test.dir/src/net/event_loop_thread.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/test.dir/src/net/event_loop_thread.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/event_loop_thread.cc.o -MF CMakeFiles/test.dir/src/net/event_loop_thread.cc.o.d -o CMakeFiles/test.dir/src/net/event_loop_thread.cc.o -c /home/spanoc/netlib/src/net/event_loop_thread.cc

CMakeFiles/test.dir/src/net/event_loop_thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/event_loop_thread.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/event_loop_thread.cc > CMakeFiles/test.dir/src/net/event_loop_thread.cc.i

CMakeFiles/test.dir/src/net/event_loop_thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/event_loop_thread.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/event_loop_thread.cc -o CMakeFiles/test.dir/src/net/event_loop_thread.cc.s

CMakeFiles/test.dir/src/net/socket.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/socket.cc.o: /home/spanoc/netlib/src/net/socket.cc
CMakeFiles/test.dir/src/net/socket.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/test.dir/src/net/socket.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/socket.cc.o -MF CMakeFiles/test.dir/src/net/socket.cc.o.d -o CMakeFiles/test.dir/src/net/socket.cc.o -c /home/spanoc/netlib/src/net/socket.cc

CMakeFiles/test.dir/src/net/socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/socket.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/socket.cc > CMakeFiles/test.dir/src/net/socket.cc.i

CMakeFiles/test.dir/src/net/socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/socket.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/socket.cc -o CMakeFiles/test.dir/src/net/socket.cc.s

CMakeFiles/test.dir/src/net/tcp_connection.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/tcp_connection.cc.o: /home/spanoc/netlib/src/net/tcp_connection.cc
CMakeFiles/test.dir/src/net/tcp_connection.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/test.dir/src/net/tcp_connection.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/tcp_connection.cc.o -MF CMakeFiles/test.dir/src/net/tcp_connection.cc.o.d -o CMakeFiles/test.dir/src/net/tcp_connection.cc.o -c /home/spanoc/netlib/src/net/tcp_connection.cc

CMakeFiles/test.dir/src/net/tcp_connection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/tcp_connection.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/tcp_connection.cc > CMakeFiles/test.dir/src/net/tcp_connection.cc.i

CMakeFiles/test.dir/src/net/tcp_connection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/tcp_connection.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/tcp_connection.cc -o CMakeFiles/test.dir/src/net/tcp_connection.cc.s

CMakeFiles/test.dir/src/net/tcp_server.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/tcp_server.cc.o: /home/spanoc/netlib/src/net/tcp_server.cc
CMakeFiles/test.dir/src/net/tcp_server.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/test.dir/src/net/tcp_server.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/tcp_server.cc.o -MF CMakeFiles/test.dir/src/net/tcp_server.cc.o.d -o CMakeFiles/test.dir/src/net/tcp_server.cc.o -c /home/spanoc/netlib/src/net/tcp_server.cc

CMakeFiles/test.dir/src/net/tcp_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/tcp_server.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/tcp_server.cc > CMakeFiles/test.dir/src/net/tcp_server.cc.i

CMakeFiles/test.dir/src/net/tcp_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/tcp_server.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/tcp_server.cc -o CMakeFiles/test.dir/src/net/tcp_server.cc.s

CMakeFiles/test.dir/src/net/timer_container.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/net/timer_container.cc.o: /home/spanoc/netlib/src/net/timer_container.cc
CMakeFiles/test.dir/src/net/timer_container.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/test.dir/src/net/timer_container.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/net/timer_container.cc.o -MF CMakeFiles/test.dir/src/net/timer_container.cc.o.d -o CMakeFiles/test.dir/src/net/timer_container.cc.o -c /home/spanoc/netlib/src/net/timer_container.cc

CMakeFiles/test.dir/src/net/timer_container.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/net/timer_container.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/src/net/timer_container.cc > CMakeFiles/test.dir/src/net/timer_container.cc.i

CMakeFiles/test.dir/src/net/timer_container.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/net/timer_container.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/src/net/timer_container.cc -o CMakeFiles/test.dir/src/net/timer_container.cc.s

CMakeFiles/test.dir/test/test_send.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/test/test_send.cc.o: /home/spanoc/netlib/test/test_send.cc
CMakeFiles/test.dir/test/test_send.cc.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/test.dir/test/test_send.cc.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/test/test_send.cc.o -MF CMakeFiles/test.dir/test/test_send.cc.o.d -o CMakeFiles/test.dir/test/test_send.cc.o -c /home/spanoc/netlib/test/test_send.cc

CMakeFiles/test.dir/test/test_send.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/test/test_send.cc.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/spanoc/netlib/test/test_send.cc > CMakeFiles/test.dir/test/test_send.cc.i

CMakeFiles/test.dir/test/test_send.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/test/test_send.cc.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/spanoc/netlib/test/test_send.cc -o CMakeFiles/test.dir/test/test_send.cc.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/src/base/async_logging.cc.o" \
"CMakeFiles/test.dir/src/base/current_thread.cc.o" \
"CMakeFiles/test.dir/src/base/file_util.cc.o" \
"CMakeFiles/test.dir/src/base/logfile.cc.o" \
"CMakeFiles/test.dir/src/base/logger.cc.o" \
"CMakeFiles/test.dir/src/base/logstream.cc.o" \
"CMakeFiles/test.dir/src/base/thread.cc.o" \
"CMakeFiles/test.dir/src/base/timestamp.cc.o" \
"CMakeFiles/test.dir/src/net/acceptor.cc.o" \
"CMakeFiles/test.dir/src/net/buffer.cc.o" \
"CMakeFiles/test.dir/src/net/channel.cc.o" \
"CMakeFiles/test.dir/src/net/epoller.cc.o" \
"CMakeFiles/test.dir/src/net/event_loop.cc.o" \
"CMakeFiles/test.dir/src/net/event_loop_thread.cc.o" \
"CMakeFiles/test.dir/src/net/socket.cc.o" \
"CMakeFiles/test.dir/src/net/tcp_connection.cc.o" \
"CMakeFiles/test.dir/src/net/tcp_server.cc.o" \
"CMakeFiles/test.dir/src/net/timer_container.cc.o" \
"CMakeFiles/test.dir/test/test_send.cc.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/src/base/async_logging.cc.o
test: CMakeFiles/test.dir/src/base/current_thread.cc.o
test: CMakeFiles/test.dir/src/base/file_util.cc.o
test: CMakeFiles/test.dir/src/base/logfile.cc.o
test: CMakeFiles/test.dir/src/base/logger.cc.o
test: CMakeFiles/test.dir/src/base/logstream.cc.o
test: CMakeFiles/test.dir/src/base/thread.cc.o
test: CMakeFiles/test.dir/src/base/timestamp.cc.o
test: CMakeFiles/test.dir/src/net/acceptor.cc.o
test: CMakeFiles/test.dir/src/net/buffer.cc.o
test: CMakeFiles/test.dir/src/net/channel.cc.o
test: CMakeFiles/test.dir/src/net/epoller.cc.o
test: CMakeFiles/test.dir/src/net/event_loop.cc.o
test: CMakeFiles/test.dir/src/net/event_loop_thread.cc.o
test: CMakeFiles/test.dir/src/net/socket.cc.o
test: CMakeFiles/test.dir/src/net/tcp_connection.cc.o
test: CMakeFiles/test.dir/src/net/tcp_server.cc.o
test: CMakeFiles/test.dir/src/net/timer_container.cc.o
test: CMakeFiles/test.dir/test/test_send.cc.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/spanoc/netlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/spanoc/netlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/spanoc/netlib /home/spanoc/netlib /home/spanoc/netlib/build /home/spanoc/netlib/build /home/spanoc/netlib/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

