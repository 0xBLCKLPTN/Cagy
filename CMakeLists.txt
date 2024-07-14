
cmake_minimum_required(VERSION 3.22)

project(Cagy LANGUAGES CXX)


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(Cagy ${SDL2_INCLUDE_DIRS})
include_directories(Cagy ${SDL2_IMAGE_INCLUDE_DIRS})
#find_package(OPENGL REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS})
#link_directories(${OPENGL_LIBRARY_DIRS})


add_executable(Cagy SourceFiles/Main.cc SourceFiles/Window.cc SourceFiles/Window.hh SourceFiles/Core.hh)
target_link_libraries(Cagy ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Cagy m)
#target_link_libraries(Cagy ${OPENGL_LIBRARIES})
