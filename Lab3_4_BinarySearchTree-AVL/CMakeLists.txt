cmake_minimum_required(VERSION 3.23)
project(Lab3_4_BinarySearchTree-AVL)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab3_4_BinarySearchTree-AVL main.cpp
        BinarySearchTree.cpp
        BinarySearchTree.h
        BinaryTree.cpp
        BinaryTree.h
        BinarySearchTreeTester.cpp
        BinarySearchTreeTester.h)
