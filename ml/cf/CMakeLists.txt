cmake_minimum_required(VERSION 3.15)
project(ml_cf)


add_definitions(-DLOCAL)
add_executable(bayes bayes.cpp) # E

add_executable(correlation correlation.cpp) # M N
add_executable(distance distance.cpp) # O
add_executable(cond_dispersion cond_dispersion.cpp) # P
add_executable(hi_2 hi_2.cpp) # Q
add_executable(cond_entropy cond_entropy.cpp) # R
