cmake_minimum_required(VERSION 2.8)

project(PERSSET)

include_directories(${PERSSET_SOURCE_DIR})

add_executable(pers_set_testing
	pers_set.h
	shared_ptr.h
	linked_ptr.h
	test.cpp
	gtest/gtest-all.cc
	gtest/gtest.h
	gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -std=c++11 -pedantic -flto")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(pers_set_testing -lpthread)