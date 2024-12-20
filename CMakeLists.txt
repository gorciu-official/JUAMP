cmake_minimum_required(VERSION 3.10)
project(JUAMP LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
# If you want to statically link program uncomment this line
# set(CMAKE_EXE_LINKER_FLAGS "-static")
# If you want to use clang uncomment this line
# set(CMAKE_CXX_COMPILER "clang++")
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_GENERATOR "Ninja")
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(juamp ${SOURCES})