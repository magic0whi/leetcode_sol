cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")

project(hello.cpp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_MODULE_STD True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wold-style-cast")
# Clean the cmake default "-O3 -DNDEBUG"
set(CMAKE_CXX_FLAGS_RELEASE "-Werror -O2 -DNDEBUG -flto")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
if(NOT PGO_TRAINING_DIR)
  SET(PGO_TRAINING_DIR "${CMAKE_BINARY_DIR}/profile_data")
endif()

if(CMAKE_BUILD_TYPE MATCHES PGOTRAIN)
  # Add the CMAKE_CXX_FLAGS_RELEASE so that a PGO optimized build also includes release flags
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -fprofile-generate=${PGO_TRAINING_DIR}")
endif()
if(CMAKE_BUILD_TYPE MATCHES PGOBUILD)
  add_custom_target(profdata_merge
    ALL
    COMMAND llvm-profdata merge -sparse *.profraw -o default.profdata
    WORKING_DIRECTORY ${PGO_TRAINING_DIR})
    # Add the CMAKE_CXX_FLAGS_RELEASE so that a PGO optimized build also includes release flags
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -fprofile-use=${PGO_TRAINING_DIR}/default.profdata")
endif()

add_executable(hello)
target_sources(hello PRIVATE main.cpp)

add_library(leetcode STATIC)
target_sources(leetcode PUBLIC FILE_SET CXX_MODULES FILES leetcode.cppm leetcode.internals.cppm leetcode.helpers.cppm)
add_library(linalg STATIC)
target_sources(linalg PUBLIC FILE_SET CXX_MODULES FILES linalg.cppm)
target_link_libraries(hello PRIVATE leetcode linalg)

enable_testing()
add_test(NAME run COMMAND hello)
add_test(NAME train COMMAND hello --train)
