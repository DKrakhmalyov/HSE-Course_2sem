cmake_minimum_required(VERSION 3.16)

project(Semester2
    VERSION
        1.0
    LANGUAGES
        CXX
)

option(HOMEWORK_1 OFF)
option(HOMEWORK_2 OFF)

if (HOMEWORK_1)
    add_subdirectory(homework-1)
elseif(HOMEWORK_2)
    add_subdirectory(homework-2)
endif(HOMEWORK_1)
