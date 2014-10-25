cmake_minimum_required(VERSION 2.8.4)
project(alg)

set(SOURCE_FILES
    main.cpp
    common/merge.hpp
    p1/IntegerArray.txt)

ADD_DEFINITIONS(
    -std=c++11
)

add_executable(alg ${SOURCE_FILES})