cmake_minimum_required(VERSION 3.6)
project(huffman_cmake)

include_directories(${huffman_cmake_SOURCE_DIR})

add_library(huffman_lib
        bits_seq.h
        bits_seq.cpp
        decoder.cpp
        encoder.cpp
        freq_tree.h
        freq_tree.cpp
        huffman_cod.h)

install(TARGETS huffman_lib DESTINATION lib)
install (FILES
        bits_seq.h
        freq_tree.h
        huffman_cod.h
        DESTINATION include/huffman_lib)

add_executable(huffman_cmake
        main.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11 -pedantic")
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address,undefined")
endif()
target_link_libraries(huffman_cmake huffman_lib)