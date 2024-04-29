//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_SHADERLIB_H
#define CG_PROJECT_SHADERLIB_H

#include "glad.h"
#include "glfw3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "../texture_images/save_load.h"

namespace open_gl
{
    GLuint bufferTextureFromFile(const char* filename, bool pixelTexture = false){
        int width, height, numChannels;
        unsigned char* imageData = texture_images::save_load::loadImage(filename, width, height, numChannels);
        if (!imageData)
        {
            std::cerr << "Failed to load the image: " << filename << std::endl;
            return -1;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Upload the pixel data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        if (pixelTexture)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the pixel data
        delete[] imageData;

        return textureID;
    }

    GLuint bufferTextureFromData(unsigned char* data, int width, int height)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Upload the pixel data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        return textureID;
    }

    // Function to generate a checkerboard texture
    GLuint generateCheckerboardTexture(int width, int height) {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Generate checkerboard pixel data
        unsigned char* data = new unsigned char[width * height * 3];
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char color = ((x / 128) + (y / 128)) % 2 == 0 ? 255 : 0;

                data[(y * width + x) * 3] = color;         // Red
                data[(y * width + x) * 3 + 1] = color;     // Green
                data[(y * width + x) * 3 + 2] = color;     // Blue

            }
        }

        // Upload the pixel data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the pixel data
        delete[] data;

        return textureID;
    }

    GLuint compileShader(const char **code, GLint type)
    {
        GLuint shader = glCreateShader(type);
        if (!shader) return -1;

        glShaderSource(shader, 1, code, NULL);
        glCompileShader(shader);

        GLint compileResult;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
        std::cout << compileResult << std::endl;
        return shader;
    }

    GLuint compileShader(const char* filePath, GLint type)
    {
        std::ifstream f(filePath);
        std::string str;
        if (f)
        {
            std::ostringstream ss;
            ss << f.rdbuf();
            str = ss.str();
        }
        const char * c = str.c_str();

        GLuint shader = glCreateShader(type);
        if (!shader) return -1;

        glShaderSource(shader, 1, &c, NULL);
        glCompileShader(shader);

        GLint compileResult;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

        if (compileResult != GL_TRUE)
        {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> log(logLength);
            glGetShaderInfoLog(shader, logLength, NULL, log.data());
            std::cerr << "Shader compilation failed: " << log.data() << ". filePath: " << filePath << std::endl;
            glDeleteShader(shader);

            return 0;
        }

        return shader;
    }

    GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader)
    {
        // Create program and link shaders to program
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint result;
        glGetProgramiv(program, GL_LINK_STATUS, &result);

        // Detach and delete shaders
        // Return program
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return program;
    }
}

#endif //CG_PROJECT_SHADERLIB_H
