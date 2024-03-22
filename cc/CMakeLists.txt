cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
SET(CXX "clang++")

if(MSVC)
    set(CXX_FLAGS
        /std:c++17
        /Za
    )
else()
    set(CXX_FLAGS
        -Wextra
        #-Wconversion
        -Wno-unused-parameter
        -Wno-old-style-cast
        -Wpointer-arith
        # -Wshadow
        # -Wwrite-strings
        -Wall
        -Wpedantic
        -march=native
        -fuse-ld=lld
        -ggdb
        -O3
    )

endif()

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


    set(T ${OBJ})
    add_executable(${T})
    target_sources(${T} PUBLIC ${CXX_SRC})
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_compile_options(${T} PRIVATE "-stdlib=libc++")
    endif()
    target_link_libraries(${T} Catch2::Catch2WithMain) 
    target_link_libraries(${T} pthread) 
    target_compile_options(${T} PRIVATE "-fsanitize=address")
    target_link_options(${T} PUBLIC "-fsanitize=address")
    
    add_test(NAME ${T} COMMAND ${T} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach ()
