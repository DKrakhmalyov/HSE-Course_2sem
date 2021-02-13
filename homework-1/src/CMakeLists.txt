cmake_minimum_required(VERSION 3.17)

project(homework_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(graph INTERFACE)

target_include_directories(graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})