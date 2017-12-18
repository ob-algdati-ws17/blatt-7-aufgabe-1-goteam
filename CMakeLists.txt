cmake_minimum_required(VERSION 3.7)
project(blatt_7_aufgabe_1_goteam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES avltree/AVLTree.cpp avltree/AVLTree.h)
add_library(blatt_7_aufgabe_1_goteam ${SOURCE_FILES})