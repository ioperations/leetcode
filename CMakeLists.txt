cmake_minimum_required(VERSION 3.19.0)
project(Leetcode LANGUAGES CXX)
option(ENABLE_COVERAGE "enable code coverage" OFF)

enable_testing()

Include(FetchContent)

find_package(Catch2 3)
# if(NOT Catch2_FOUND)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.4.0 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)
# endif()

add_subdirectory(cc)
