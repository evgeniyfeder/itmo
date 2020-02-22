cmake_minimum_required(VERSION 3.15)
project(ml_cf)


add_definitions(-DLOCAL)
add_executable(bayes bayes.cpp)
add_executable(correlation matstat.cpp)
