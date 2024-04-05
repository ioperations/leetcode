cmake_minimum_required(VERSION 3.19.0)
project(Leetcode LANGUAGES CXX)
option(ENABLE_COVERAGE "enable code coverage" OFF)

enable_testing()
include(FetchContent)

FetchContent_Declare(
  gtest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0 # or a later release
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

FetchContent_Declare(
    gbench
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.3
)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(gbench)

add_subdirectory(cc)
