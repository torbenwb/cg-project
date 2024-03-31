cmake_minimum_required(VERSION 3.21)
project(cg_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(Inc)
include_directories(Inc/freetype)
include_directories(Inc/freetype/config)
include_directories(Inc/GL)
include_directories(GraphicsLayer/Include)
find_package(glfw3 3.4 REQUIRED)

#
#add_executable(cg_project assignment_4.cpp
#        Lib/GLXtras.cpp
#        Lib/glad.c
#        Lib/window.cpp Inc/ECS/Entity.h Lib/ECS/Entity.cpp Inc/ECS/Component.h Lib/ECS/Component.cpp Inc/ECS/Object.h Lib/ECS/Object.cpp Inc/ECS/ECS.h Inc/ECS/Transform.h
#        Lib/Camera.cpp
#        Lib/Draw.cpp
#        Lib/IO.cpp
#        Lib/Widgets.cpp
#        Lib/Quaternion.cpp
#        Lib/Text.cpp
#        Lib/Letters.cpp)

add_executable(cg_project test.cpp
        Lib/GLXtras.cpp
        Lib/glad.c
        Lib/window.cpp
        GraphicsLayer/Include/GraphicsLayer.h
        GraphicsLayer/Include/MeshRenderer.h
        GraphicsLayer/Library/MeshRenderer.cpp
        GraphicsLayer/Include/MeshData.h
        GraphicsLayer/Include/ShaderCompiler.h
        GraphicsLayer/Library/ShaderCompiler.cpp
        GraphicsLayer/Library/MeshData.cpp
        GraphicsLayer/Include/Transform.h GraphicsLayer/Library/Transform.cpp
        GraphicsLayer/Include/Projection.h
        Engine/Include/Time.h Engine/Library/Time.cpp
        Engine/Include/Engine.h Engine/Library/Engine.cpp)

target_link_libraries(cg_project glfw)
