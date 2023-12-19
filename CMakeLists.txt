cmake_minimum_required(VERSION 3.5)
project(netlib)

set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wthread-safety -fsanitize=thread")
# 想要生成coredump文件，就不能用 -fsanitize=thread
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wthread-safety")
# 检测内存泄漏
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wthread-safety -fsanitize=leak")
# 调试选项
set(CMAKE_BUILD_TYPE DEBUG)
# 优化选项
# set(CMAKE_CXX_FLAGS_RELEASE)

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SRC_NET)
# aux_source_directory(test TESTS)

add_executable(server ${SRC_BASE} ${SRC_NET} test/test_apachebench.cc)
add_library(netlib_static ${SRC_BASE} ${SRC_NET})