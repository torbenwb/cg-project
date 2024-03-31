// 2-ClearScreen-Mac.cpp - OpenGL test program for Apple Silicon architecture

#include "glad.h" // GL header file
#include <GLFW/glfw3.h>       // GL toolkit
#include <stdio.h>			// printf, etc
#include "window.h"
#include "GraphicsLayer.h"
#include <glm/glm.hpp>
#include "Engine/Include/Engine.h"

GLuint program = 0;			// shader prog ID, valid if > 0


int winWidth = 400, winHeight = 400;

// vertex shader: operations before the rasterizer
const char *vertexShader = R"(
    #version 330 core
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 perspective;
    layout (location=0) in vec3 point;
    layout (location=1) in vec3 normal;
    layout (location=2) in vec3 color;
    layout (location=3) in vec2 uv;

    out vec3 outPoint;
    out vec3 outNormal;
    out vec3 outColor;

    void main() {
        outPoint = point;
        vec4 worldPosition = model * vec4(outPoint, 1);
        vec4 viewPosition = view * worldPosition;

        gl_Position = perspective * viewPosition;

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

class TestEngine : public Engine
{
    GLFWwindow* window;
    virtual void runStartupLogic()
    {
        MeshData testMeshData;
        testMeshData.loadOBJ("/Users/torbenbernhard/Desktop/Seattle U/cg-project/cube.obj");

        window = initWindow(0, 0, 200, 200,"Title");

        MeshRenderer testMesh = MeshRenderer();

        testMesh.meshData = &testMeshData;
        testMesh.Buffer();

        GLuint vertexProgram = compileShader(&vertexShader, GL_VERTEX_SHADER);
        GLuint fragmentProgram = compileShader(&pixelShader, GL_FRAGMENT_SHADER);
        program = linkShaderProgram(vertexProgram, fragmentProgram);

        Transform model = Transform();
        Transform view = Transform();
        view.position.z = -5.0f;
        Projection projection = Projection(1.0f, 1.0f, 0.1f, 100.0f);

        glm::vec3 viewRotation = glm::vec3(0.0f, 0.0f, 0.0f);
        close = glfwWindowShouldClose(window);
    }

    virtual void runAppLogic()
    {

    }

    virtual void runDisplayLogic()
    {
        // Clear background
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        // Enable Depth Test
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glDisable(GL_DEPTH_TEST);
        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
        close = glfwWindowShouldClose(window);
    }

    virtual void runCloseLogic()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main()
{
    TestEngine testEngine = TestEngine();
    testEngine.run();
    return 0;
    MeshData testMeshData;
    testMeshData.loadOBJ("/Users/torbenbernhard/Desktop/Seattle U/cg-project/cube.obj");

    GLFWwindow* window = initWindow(0, 0, 200, 200,"Title");

    MeshRenderer testMesh = MeshRenderer();

    testMesh.meshData = &testMeshData;
    testMesh.Buffer();

    GLuint vertexProgram = compileShader(&vertexShader, GL_VERTEX_SHADER);
    GLuint fragmentProgram = compileShader(&pixelShader, GL_FRAGMENT_SHADER);
    program = linkShaderProgram(vertexProgram, fragmentProgram);

    Transform model = Transform();
    Transform view = Transform();
    view.position.z = -5.0f;
    Projection projection = Projection(1.0f, 1.0f, 0.1f, 100.0f);

    glm::vec3 viewRotation = glm::vec3(0.0f, 0.0f, 0.0f);


    while (!glfwWindowShouldClose(window)) {
        // Clear background
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        // Enable Depth Test
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        view.rotation = glm::quat(viewRotation);
        testMesh.Render(program, model, view, projection);

        glDisable(GL_DEPTH_TEST);
        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
