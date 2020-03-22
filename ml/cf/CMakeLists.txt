cmake_minimum_required(VERSION 3.15)
project(ml_cf)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DLOCAL)

add_executable(liner linear.cpp) # D
add_executable(svm svm.cpp) # E
add_executable(bayes bayes.cpp) # F
add_executable(logic_expr logic_expr.cpp) # I

add_executable(correlation correlation.cpp) # M N
add_executable(distance distance.cpp) # O
add_executable(cond_dispersion cond_dispersion.cpp) # P
add_executable(hi_2 hi_2.cpp) # Q
add_executable(cond_entropy cond_entropy.cpp) # R
