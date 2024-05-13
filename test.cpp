// 2-ClearScreen-Mac.cpp - OpenGL test program for Apple Silicon architecture

#include "glad.h" // GL header file
#include <GLFW/glfw3.h>       // GL toolkit
#include <iostream>
#include <glm/glm.hpp>

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
    Window window;
    MeshData* testMeshData;
    MeshRenderer testMeshRenderer;
    Transform model;
    Transform view;
    Projection projection;
    glm::vec3 testControlRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    virtual void runStartupLogic()
    {
        testMeshData = new MeshData();
        testMeshData->loadOBJ("/Users/torbenbernhard/Desktop/Seattle U/cg-project/cube.obj");
        //testMeshData->generatePlane(10, 10);
        window = Window(500, 500, "Title");
        window.open();
        testMeshRenderer = MeshRenderer();

        testMeshRenderer.meshData = testMeshData;
        testMeshRenderer.Buffer();

        GLuint vertexProgram = compileShader(&vertexShader, GL_VERTEX_SHADER);
        GLuint fragmentProgram = compileShader(&pixelShader, GL_FRAGMENT_SHADER);
        program = linkShaderProgram(vertexProgram, fragmentProgram);

        model = Transform();
        view = Transform();
        view.position.z = -5.0f;
        view.rotation = glm::quat();
        projection = Projection(1.0f, 1.0f, 0.1f, 100.0f);

        glm::vec3 viewRotation = glm::vec3(0.0f, 0.0f, 0.0f);
        close = window.getShouldClose();
    }

    virtual void runAppLogic()
    {
        float deltaTime = 0.01f;
        glm::vec3 moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
        float moveSpeed = 10.0f;

        if (window.getKey(GLFW_KEY_W))
        {
            moveVector += view.getForward();
        }
        if (window.getKey(GLFW_KEY_S))
        {
            moveVector -= view.getForward();
        }
        if (window.getKey(GLFW_KEY_A))
        {
            moveVector -= view.getRight();
        }
        if (window.getKey(GLFW_KEY_D))
        {
            moveVector += view.getRight();
        }
        if (window.getKey(GLFW_KEY_SPACE))
        {
            moveVector += view.getUp();
        }

        view.position += moveVector * moveSpeed * deltaTime;



        if (window.getKey(GLFW_KEY_LEFT))
        {
            testControlRotation.y -= 0.01f;
        }
        if (window.getKey(GLFW_KEY_RIGHT))
        {
            testControlRotation.y += 0.01f;
        }

        view.rotation = glm::quat(testControlRotation);
    }

    virtual void runDisplayLogic()
    {
        // Clear background
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        // Enable Depth Test
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        testMeshRenderer.Render(program, model, view, projection);

        glDisable(GL_DEPTH_TEST);
        glFlush();
        window.update();
        close = window.getShouldClose();
    }

    virtual void runCloseLogic()
    {
        window.close();
    }
};

class SceneEngine : public Engine
{
    Window* window;

    void runStartupLogic() override
    {

    }

    void runAppLogic() override
    {

    }

    void runDisplayLogic() override
    {

    }
};

int main()
{
    TestEngine testEngine = TestEngine();
    testEngine.run();
    return 0;
}
