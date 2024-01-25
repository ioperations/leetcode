cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
SET(CXX "clang++")

set(CXX_FLAGS
        # -Wextra
        #-Wconversion
        # -Wno-unused-parameter
        # -Wold-style-cast
        # -Wpointer-arith
        # -Wshadow
        # -Wwrite-strings
        -Wall
        -Wpedantic
        -march=native
        -DTEST_ADQ
        -fuse-ld=lld
        -g
        -O2
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


set(leetcode ${OBJ_FILES})


foreach (curlist ${leetcode})
    get_filename_component(test1 ${curlist} NAME_WLE)
    add_executable(${test1} ${test1}.cc)
    target_compile_definitions(${test1} PUBLIC "TEST_ADQ")
    target_compile_options(${test1} PUBLIC "-std=c++17")
    target_compile_options(${test1} PRIVATE "-fsanitize=address")
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_compile_options(${test1} PRIVATE "-stdlib=libc++")
    endif()
    target_include_directories(${test1} PUBLIC "/usr/local/include")
    target_link_directories(${test1} PUBLIC "/usr/local/lib")
    target_link_libraries(${test1} gtest pthread benchmark)
    target_link_options(${test1} PUBLIC "-fsanitize=address")

    add_test(NAME ${test1} COMMAND ${test1} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach ()
