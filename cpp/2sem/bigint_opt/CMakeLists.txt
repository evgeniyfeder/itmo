cmake_minimum_required(VERSION 2.8)

project(BIGINT)

include_directories(${BIGINT_SOURCE_DIR})

add_executable(big_integer_testing
               big_integer_testing.cpp
               big_integer.h
               additions.cpp
        arithmetic.cpp
        constructors.cpp
        infix.cpp
        logical.cpp
        shifts.cpp
        vector/my_vector.cpp
        vector/my_vector.h
        gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -flto -Wall -std=c++11 -pedantic -flto")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(big_integer_testing -lpthread)
