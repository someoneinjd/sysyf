cmake_minimum_required(VERSION 3.14)

project(SysYFCompiler)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wno-unused -Wshadow -g -pedantic")
elseif(CMAKE_BUILD_TYPE STREQUAL "Asan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wno-unused -Wshadow -g -pedantic -fsanitize=address -fno-omit-frame-pointer")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -Wextra -Wno-unused -Wshadow")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/AST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Parser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/IR)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Support)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/atn)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/dfa)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/internal)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/misc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/support)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/tree)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/tree/pattern)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ANTLRRuntime/tree/xpath)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/ANTLRRuntime)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/Parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/AST)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/IR)

add_executable(
  compiler
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(
  compiler
  Parser
  AST
  IR
  ANTLRRuntime
)
