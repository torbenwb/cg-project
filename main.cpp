// 2-ClearScreen-Mac.cpp - OpenGL test program for Apple Silicon architecture

#include "glad.h" // GL header file
#include <GLFW/glfw3.h>       // GL toolkit
#include <stdio.h>			// printf, etc
#include "GLXtras.h"		// convenience routines

const unsigned int SCREEN_WIDTH = 400;
const unsigned int SCREEN_HEIGHT = 400;
vec3 userColor(0, 1, 0);
vec3 colorOne(0.5, 0.1, 0.1);
vec3 colors[] = {
        vec3(0.5f, 0.1f, 0.1f),
        vec3(0.1f, 0.5f, 0.5f)
};
int colorIndex = 0;
unsigned int shaderProgram;



void glfwError(int i, const char * c)
{
    printf("GLFW ERROR: %s", c);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        colorIndex++;
        if (colorIndex >= 2)
        {
            colorIndex = 0;
        }
        //userColor = vec3(0.7, 0.1, 0.2);
        userColor = colors[colorIndex];
        GLint id = glGetUniformLocation(shaderProgram, "userColor");
        glUniform3f(id, userColor.x, userColor.y, userColor.z);
    }
}

int main()
{
    // Init GLFW and setup Error Callback
    glfwSetErrorCallback(glfwError);
    if (!glfwInit())
    {
        std::cout << "failed glfw init";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          "Assignment 1",
                                          NULL,
                                          NULL);

    if (window == NULL)
    {
        std::cout << "Window is Null" << std::endl;
        glfwTerminate();
        return  -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Print vendor, version info
    printf("GL vendor: %s\n", glGetString(GL_VENDOR));
    printf("GL renderer: %s\n", glGetString(GL_RENDERER));
    printf("GL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


    /// Vertex Shader Setup
    float vertices[] =
            {
                    -1.0f, -1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    -1.0f, 1.0f, 0.0f,

                    -1.0f,1.0f, 0.0f,
                    1.0f, -1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
            };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderSource =R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        }
    )";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    /// Fragment Shader
    const char * fragmentShaderSource = R"(
        #version 330 core
        uniform vec3 userColor;
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(userColor, 1.0);
        }
    )";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    ///

    /// Shader Program

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
    glUseProgram(shaderProgram);
    // Delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    ///
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // copy vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Use shader program when to render an object
    glUseProgram(shaderProgram);
    //
    ///
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // copy vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    ///

    // Set Uniform
    GLint id = glGetUniformLocation(shaderProgram, "userColor");
    userColor = colors[colorIndex];
    glUniform3f(id, userColor.x, userColor.y, userColor.z);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
