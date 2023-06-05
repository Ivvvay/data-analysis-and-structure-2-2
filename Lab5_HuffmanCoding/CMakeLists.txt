cmake_minimum_required(VERSION 3.23)
project(Lab5_HuffmanCoding)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab5_HuffmanCoding main.cpp
        HuffmanCoding.cpp HuffmanCoding.h
        Set.cpp Set.h)
