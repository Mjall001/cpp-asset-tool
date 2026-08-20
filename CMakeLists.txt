#Minimum version of the Cmake version supported
cmake_minimum_required(VERSION 4.4.2)

#Project name
project(cpp-asset-tool)

#Speciy the c++ stantdard we are going to use C++11
set(CMAKE_CXX_STANDARD 11)

#Specify the source code files to current project
add_executable(HelloWorld src/main.cpp)