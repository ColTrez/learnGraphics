cmake_minimum_required(VERSION 3.21.3)

project(learnGraphics)

add_executable(${PROJECT_NAME} SRC/ex_shader.cpp)

add_subdirectory(EXT/glfw)
add_subdirectory(EXT/glad)
add_subdirectory(EXT/soil)
#add_subdirectory(EXT/freeglut)
#add_subdirectory(EXT/glload)

add_link_options(-lGl)

target_link_libraries(${PROJECT_NAME} glfw glad SOIL)
