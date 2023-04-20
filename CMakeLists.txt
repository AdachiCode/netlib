cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wthread-safety -fsanitize=thread")
set(CMAKE_BUILD_TYPE DEBUG)

include_directories(include)

aux_source_directory(src/base SRC_BASE)
aux_source_directory(src/net SRC_NET)
# aux_source_directory(test TESTS)

add_executable(${PROJECT_NAME} ${SRC_BASE} ${SRC_NET} test/test_threadpool.cc)