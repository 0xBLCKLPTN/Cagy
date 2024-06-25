cmake_minimum_required(VERSION 3.22)

project(Cagy LANGUAGES C)


find_package(SDL2 REQUIRED)
include_directories(Cagy ${SDL2_INCLUDE_DIRS})


add_executable(Cagy core/window.c)
target_link_libraries(Cagy ${SDL2_LIBRARIES})
