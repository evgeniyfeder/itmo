project(ShalytoLab)

set (CMAKE_CXX_STANDARD 17)

add_executable(mutation mutation.cpp)
add_executable(crossover crossover.cpp)
add_executable(trees trees.cpp)
add_executable(start start.cpp)
add_executable(discrete discrete.cpp)
add_executable(inter_minim inter_minim.cpp)
add_executable(artificial artificial.cpp)

