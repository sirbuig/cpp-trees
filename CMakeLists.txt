cmake_minimum_required(VERSION 3.28)
project(trees)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(trees main.cpp
        include/Node.h
        include/Treap.h
        include/Tree.h
        src/Treap.tpp
        include/SplayTree.h
        src/SplayTree.tpp
)
