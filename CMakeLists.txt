cmake_minimum_required(VERSION 3.0.0)
project(Leetcode LANGUAGES CXX)
option(ENABLE_COVERAGE "enable code coverage" OFF)

enable_testing()
add_subdirectory(leetcode)
