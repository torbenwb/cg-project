cmake_minimum_required(VERSION 3.21)
project(cg_project)

set(CMAKE_CXX_STANDARD 14)

set(run "build")

include_directories(Inc)
include_directories(Inc/freetype)
include_directories(Inc/freetype/config)
include_directories(Inc/GL)
include_directories(open_gl)
include_directories(math)
find_package(glfw3 3.4 REQUIRED)




if (run STREQUAL "build")
    add_executable(cg_project main.cpp
            Lib/glad.c
            open_gl/window.cpp open_gl/window.h
            open_gl/mesh.cpp open_gl/mesh.h
            open_gl/shaderLib.h
            math/transform.cpp math/transform.h
            math/projection.h
            open_gl/camera.cpp open_gl/camera.h
            open_gl/renderer.h
            open_gl/input.cpp open_gl/input.h math/random.h open_gl/scene.cpp open_gl/scene.h open_gl/light.h open_gl/voxel.h noise/PerlinNoise.cpp noise/PerlinNoise.h
            open_gl/stb_image.h
            texture_images/save_load.h
            texture_images/generate.h
            texture_images/atlas.h)
elseif(run STREQUAL "ti_tests")
    add_executable(cg_project texture_images/texture_images_tests.cpp texture_images/atlas.h)
endif()


target_link_libraries(cg_project glfw)
