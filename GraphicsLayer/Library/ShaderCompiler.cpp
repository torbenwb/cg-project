//
// Created by Torben Bernhard on 3/28/24.
//

#include "glad.h"
#include <GLFW/glfw3.h>
#include "ShaderCompiler.h"

GLuint compileShader(const char **shaderCode, GLint shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    // TODO: Log error
    if (!shader) return -1;

    glShaderSource(shader, 1, shaderCode, NULL);
    glCompileShader(shader);

    // TODO: result / error handling
    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    return shader;
}

GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint linkResult;
    // TODO: error handling
    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}


