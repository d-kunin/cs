cmake_minimum_required(VERSION 2.8.4)
project(alg)

set(SOURCE_FILES
    main.cpp
    common/merge.hpp
    common/quicksort.hpp
    common/coding.hpp
    common/graph.hpp)

ADD_DEFINITIONS(
    -std=c++11
    -Wall
)

add_executable(alg ${SOURCE_FILES})

# Copy resources
add_custom_command(TARGET alg PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:alg>)