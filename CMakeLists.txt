cmake_minimum_required(VERSION 3.5)
project(netlib)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wthread-safety -fsanitize=thread")
set(CMAKE_BUILD_TYPE DEBUG)

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET)
# aux_source_directory(test TESTS)

add_executable(client ${SRC_BASE} ${SRC_NET} test/test_client.cc)
add_library(netlib_static ${SRC_BASE} ${SRC_NET})