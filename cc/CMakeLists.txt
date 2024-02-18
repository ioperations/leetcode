cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
SET(CXX "clang++")

set(CXX_FLAGS
        -Wextra
        #-Wconversion
        -Wno-unused-parameter
        # -Wold-style-cast
        -Wpointer-arith
        # -Wshadow
        # -Wwrite-strings
        -Wall
        -Wpedantic
        -march=native
        -fuse-ld=lld
        -g
        -O3
        )

enable_testing()

file(GLOB source_list "*.cc")

if(ENABLE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # using Clang
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # using GCC
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

foreach (CXX_SRC ${source_list})
    string(REGEX REPLACE "\\.cc" "" OBJ ${CXX_SRC})
    string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" OBJ ${OBJ})
    set(OBJ_FILES ${OBJ_FILES} ${OBJ})
endforeach ()


set(T leetcode)
add_executable(leetcode)
target_sources(leetcode PUBLIC ${source_list})
target_compile_options(${T} PUBLIC "-std=c++17")
target_compile_options(${T} PRIVATE "-fsanitize=address")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_options(${T} PRIVATE "-stdlib=libc++")
endif()
target_include_directories(${T} PUBLIC "/usr/local/include")
target_link_directories(${T} PUBLIC "/usr/local/lib")
target_link_libraries(${T} gtest gtest_main pthread benchmark)
target_link_options(${T} PUBLIC "-fsanitize=address")

add_test(NAME ${T} COMMAND ${T} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
