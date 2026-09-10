#Minimum version of the Cmake version supported
cmake_minimum_required(VERSION 4.4.2)

#Project name
project(cpp-asset-tool)

#Speciy the c++ stantdard we are going to use C++11
set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

#Specify the source code files to current project
add_executable(AssetLister src/main.cpp src/AssetScanner.cpp src/Validator.cpp)
#add_executable(Main src/main.cpp src/main.cpp)
#add_executable(Validator src/main.cpp src/Validator.cpp)

target_include_directories(AssetLister PUBLIC include)