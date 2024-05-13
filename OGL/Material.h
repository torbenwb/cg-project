//
// Created by Torben Bernhard on 5/11/24.
//

#ifndef CG_PROJECT_MATERIAL_H
#define CG_PROJECT_MATERIAL_H

#include "glad.h"
#include "glfw3.h"

namespace OGL
{
    class Material
    {
        const char* vertexShaderFilePath;
        const char* fragmentShaderFilePath;
        const char* textureFilePath;

        GLuint shaderProgram;

    public:
        void compile();
        GLuint getShaderProgram(){return shaderProgram;}
        Material(const char* vsPath, const char* fsPath, const char* tPath):
        vertexShaderFilePath(vsPath), fragmentShaderFilePath(fsPath), textureFilePath(tPath){}
    };
}




#endif //CG_PROJECT_MATERIAL_H
