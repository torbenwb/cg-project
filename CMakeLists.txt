cmake_minimum_required(VERSION 3.21)
project(cg_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(Inc)
find_package(glfw3 3.4 REQUIRED)

add_executable(cg_project main.cpp
        Lib/GLXtras.cpp
        Lib/glad.c)

target_link_libraries(cg_project glfw)
