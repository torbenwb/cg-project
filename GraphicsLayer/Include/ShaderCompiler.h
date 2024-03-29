//
// Created by Torben Bernhard on 3/28/24.
//

#ifndef CG_PROJECT_SHADERCOMPILER_H
#define CG_PROJECT_SHADERCOMPILER_H


GLuint compileShader(const char **shaderCode, GLint shaderType);

GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader);

#endif //CG_PROJECT_SHADERCOMPILER_H
