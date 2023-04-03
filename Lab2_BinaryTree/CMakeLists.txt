cmake_minimum_required(VERSION 3.23)
project(Lab2_BinaryTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2_BinaryTree main.cpp
        BinaryTree.cpp
        BinaryTree.h
        BinaryTreeTester.cpp
        BinaryTreeTester.h)
