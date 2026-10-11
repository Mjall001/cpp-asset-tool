#Minimum version of the Cmake version supported
cmake_minimum_required(VERSION 4.4.4)

#
#
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

#Project name
project(Asset_Validator_Tool)

#Speciy the c++ stantdard we are going to use C++11
set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenSSL REQUIRED)

#Specify the source code files to current project
add_executable(AssetLister src/main.cpp src/AssetScanner.cpp src/Validator.cpp src/DuplicateDetector.cpp)

file(GLOB_RECURSE AssetLister_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl")

target_sources(AssetLister PRIVATE ${AssetLister_SOURCES})



find_package(OpenSSL REQUIRED)
find_package(glew REQUIRED)
target_link_libraries(AssetLister PRIVATE OpenSSL::SSL OpenSSL::Crypto GLEW::GLEW)

target_include_directories(AssetLister PUBLIC include)

if(MSVC)
    target_compile_options(AssetLister PRIVATE 
        /W3
        /MP
        /WX
        /ZI
    )
else()
    target_compile_options(AssetLister PRIVATE
        -WALL
        -Wextra
        -Wpedantic
    )
endif()

#
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AssetLister)

#
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${AssetLister_SOURCES})

#
set_property(GLOBAL PROPERTY USE_FOLDERS ON)