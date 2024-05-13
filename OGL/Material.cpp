//
// Created by Torben Bernhard on 5/11/24.
//

#include "Material.h"
#include "ShaderLib.h"

namespace OGL
{
    void OGL::Material::compile()
    {
        GLuint vertexShader = ShaderLib::compileShader(vertexShaderFilePath, GL_VERTEX_SHADER);
        GLuint fragmentShader = ShaderLib::compileShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
        shaderProgram = ShaderLib::linkShaderProgram(vertexShader, fragmentShader);
        GLuint textureId = ShaderLib::bufferTextureFromFile(textureFilePath, true);

        // Get the uniform location of the texture sampler
        GLint textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");

        // Set the active texture unit and bind the texture to it
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Set the value of the uniform to the texture unit index
        glUniform1i(textureLocation, 0); // 0 is the texture unit index
    }

}

