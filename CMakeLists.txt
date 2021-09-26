cmake_minimum_required(VERSION 3.21.3)

project(learnGraphics)

add_executable(${PROJECT_NAME} SRC/main.cpp)

#add_subdirectory(SRC/)

add_subdirectory(EXT/glfw)
