cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_PREFIX_PATH "/usr")
set(CMAKE_SYSTEM_PREFIX_PATH "/usr")
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")

project(hello.cpp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_MODULE_STD True)

include_directories("/usr/include")

add_compile_options($<$<CONFIG:Debug>:-fsanitize=address>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address>)

add_library(test STATIC)
target_sources(test PUBLIC FILE_SET CXX_MODULES FILES test.cppm)
add_executable(hello)
target_sources(hello PRIVATE hello.cpp)
target_link_libraries(hello PRIVATE test)
