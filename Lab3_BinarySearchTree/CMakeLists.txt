cmake_minimum_required(VERSION 3.23)
project(Lab3_BinarySearchTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3_BinarySearchTree main.cpp
        BinarySearchTree.cpp
        BinarySearchTree.h
        BinaryTree.cpp
        BinaryTree.h
        BinarySearchTreeTester.cpp
        BinarySearchTreeTester.h)
