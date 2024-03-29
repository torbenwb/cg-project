// 2-ClearScreen-Mac.cpp - OpenGL test program for Apple Silicon architecture

#include "glad.h" // GL header file
#include <GLFW/glfw3.h>       // GL toolkit
#include <stdio.h>			// printf, etc
#include "window.h"
#include "GraphicsLayer.h"


GLuint program = 0;			// shader prog ID, valid if > 0


int winWidth = 400, winHeight = 400;

// vertex shader: operations before the rasterizer
const char *vertexShader = R"(
    #version 330 core
    uniform mat4 modelView, cameraView, perspective;
    layout (location=0) in vec3 point;
    layout (location=1) in vec3 normal;
    layout (location=2) in vec3 color;
    layout (location=3) in vec2 uv;

    out vec3 outPoint;
    out vec3 outNormal;
    out vec3 outColor;

    void main() {
        outPoint = vec4(point, 1).xyz;
        gl_Position = vec4(outPoint, 1);

        outNormal = normal;
        outColor = color;
    }
)";

// pixel shader: operations after the rasterizer
const char *pixelShader = R"(
    #version 330 core
    in vec3 outPoint;
    in vec3 outNormal;
    in vec3 outColor;

    out vec4 pColor;
    void main() {
        // REQUIREMENT 1B) shade pixel:
        pColor = vec4(outColor, 1);
    }
)";



int main()
{
    MeshData testMeshData;
    testMeshData.loadOBJ("/Users/torbenbernhard/Desktop/Seattle U/cg-project/cube.obj");

    GLFWwindow* window = initWindow(0, 0, 200, 200,"Title");

    MeshRenderer testMesh = MeshRenderer();
    MeshData meshData;
    meshData.vertices.emplace_back(-1,-1, 0);
    meshData.vertices.emplace_back(-1, 1, 0);
    meshData.vertices.emplace_back(1, 1, 0);
    meshData.vertices.emplace_back(1, -1, 0);

    meshData.normals.emplace_back(0, 1, 1);
    meshData.normals.emplace_back(1, 1, 0);
    meshData.normals.emplace_back(1, 0, 1);
    meshData.normals.emplace_back(1, 1, 1);

    meshData.colors.emplace_back(1, 0, 0);
    meshData.colors.emplace_back(1, 1, 0);
    meshData.colors.emplace_back(1, 0, 1);
    meshData.colors.emplace_back(1, 1, 1);

    meshData.triangles.push_back(0);
    meshData.triangles.push_back(1);
    meshData.triangles.push_back(2);

    meshData.triangles.push_back(2);
    meshData.triangles.push_back(3);
    meshData.triangles.push_back(0);

    testMesh.meshData = &meshData;
    testMesh.Buffer();

    GLuint vertexProgram = compileShader(&vertexShader, GL_VERTEX_SHADER);
    GLuint fragmentProgram = compileShader(&pixelShader, GL_FRAGMENT_SHADER);
    program = linkShaderProgram(vertexProgram, fragmentProgram);

    while (!glfwWindowShouldClose(window)) {
        testMesh.Render(program);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glFlush();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
