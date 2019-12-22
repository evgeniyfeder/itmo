project(LRU_CACHE)

cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unknown-pragmas -fprofile-arcs -ftest-coverage")

file(GLOB_RECURSE lru_cache_headers include/lru_cache/*.h)
add_library(lru_cache INTERFACE)
target_sources(lru_cache INTERFACE ${lru_cache_headers})
target_include_directories(lru_cache INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

find_package(GTest REQUIRED)
add_executable(lru_cache_test_ex test/lru_cache.cpp)
target_link_libraries(lru_cache_test_ex PRIVATE lru_cache GTest::GTest GTest::Main)
add_test(NAME lru_cache_test COMMAND lru_cache_test_ex)

