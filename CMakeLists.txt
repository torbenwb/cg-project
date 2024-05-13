cmake_minimum_required(VERSION 3.21)
project(cg_project)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(run "build")

include_directories(Inc)
include_directories(Inc/freetype)
include_directories(Inc/freetype/config)
include_directories(Inc/GL)
include_directories(open_gl)
include_directories(math)
include_directories(tests)
include_directories(OGL)
find_package(glfw3 3.4 REQUIRED)




if (run STREQUAL "build")
    add_executable(cg_project main.cpp
            Lib/glad.c
            open_gl/window.cpp open_gl/window.h
            open_gl/mesh.cpp open_gl/mesh.h

            math/transform.cpp math/transform.h
            math/projection.h
            open_gl/camera.cpp open_gl/camera.h
            open_gl/renderer.h
            open_gl/input.cpp open_gl/input.h math/random.h open_gl/scene.cpp open_gl/scene.h open_gl/light.h open_gl/voxel.h noise/PerlinNoise.cpp noise/PerlinNoise.h

            texture_images/save_load.h
            texture_images/generate.h
            texture_images/atlas.h
            OGL/MeshData.h
            OGL/Scene.cpp OGL/Scene.h
            OGL/Mesh.cpp OGL/Mesh.h
            OGL/MeshRenderer.h
            OGL/Transform.h OGL/Material.cpp OGL/Material.h OGL/ShaderLib.h
            texture_images/save_load.cpp Voxel/Chunk.cpp Voxel/Chunk.h Voxel/World.cpp Voxel/World.h Voxel/ChunkLoader.cpp Voxel/ChunkLoader.h)
    target_link_libraries(cg_project glfw)
elseif(run STREQUAL "test")
    #add_executable(cg_project texture_images/texture_images_tests.cpp texture_images/atlas.h mesh/MeshData.h)
    enable_testing()

    add_executable(
            hello_test
            hello_test.cc
    )
    target_link_libraries(
            hello_test
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(hello_test)
endif()



