cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
SET(CXX "clang++")

set(CXX_FLAGS
        -DVALGRIND
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -pg
        #-Wextra
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        -MMD
        -DTEST_ADQ
        -fuse-ld=lld
        -g
        -Oz
        )

enable_testing()

file(GLOB source_list "*.cc")

foreach (CXX_SRC ${source_list})
    string(REGEX REPLACE "\\.cc" "" OBJ ${CXX_SRC})
    string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" OBJ ${OBJ})
    set(OBJ_FILES ${OBJ_FILES} ${OBJ})
endforeach ()


set(leetcode ${OBJ_FILES})


foreach (curlist ${leetcode})
    #  string(REGEX REPLACE "/" "" test1 ${curlist})
    # file(RELATIVE_PATH buildDirRelFilePath "${CMAKE_CURRENT_LIST_DIR}" "${curlist}")
    get_filename_component(test1 ${curlist} NAME_WLE)
    get_filename_component(dirname ${curlist} DIRECTORY)
    add_executable(${test1} ${test1}.cc)
    target_link_libraries(${test1} gtest pthread benchmark)
    target_compile_options(${test1} PUBLIC "-DTEST_ADQ")
    target_compile_options(${test1} PUBLIC "-std=c++17")
    target_compile_options(${test1} PUBLIC "-Wall")
    target_compile_options(${test1} PRIVATE "-fsanitize=address")
    target_compile_options(${test1} PUBLIC "-I/usr/local/include")
    target_link_directories(${test1} PUBLIC "/usr/local/lib")
    target_link_options(${test1} PRIVATE "-fsanitize=address")

    add_test(NAME ${test1} COMMAND ${test1} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach ()
