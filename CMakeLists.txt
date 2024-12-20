cmake_minimum_required(VERSION 3.10)
project(JUAMP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
# If you want to statically link program uncomment this line
# set(CMAKE_EXE_LINKER_FLAGS "-static")
# If you want to use clang uncomment this line
# set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_GENERATOR "Ninja")
include_directories(src/include)
file(GLOB SOURCES "src/*.cpp")
add_executable(juamp ${SOURCES})