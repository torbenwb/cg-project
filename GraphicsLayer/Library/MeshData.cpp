//
// Created by Torben Bernhard on 3/28/24.
//

#include "MeshData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

bool vertRegex(std::string line, vec3& result)
{
    // Regular expression pattern to match a vertex line
    std::regex vertex_regex("v\\s+(-?\\d+\\.\\d+)\\s+(-?\\d+\\.\\d+)\\s+(-?\\d+\\.\\d+)");

    std::smatch match;

    if (!std::regex_search(line, match, vertex_regex)) {
        return false;
    }

    if (match.size() < 4)
    {
        return false;
    }

    float v1 = std::stof(match[1]);
    float v2 = std::stof(match[2]);
    float v3 = std::stof(match[3]);

    result = vec3(v1, v2, v3);
    return true;
}

bool uvRegex(std::string line, vec2& result)
{
    std::regex uv_regex("vt\\s+(-?\\d+\\.\\d+)\\s+(-?\\d+\\.\\d+)");

    std::smatch match;

    if (!std::regex_search(line, match, uv_regex))
    {
        return false;
    }

    float u = std::stof(match[1]);
    float v = std::stof(match[2]);

    result = vec2(u, v);
    return true;
}

bool faceRegex(std::string line)
{
    std::regex pattern("^(?:#\\sf|f)");
    return std::regex_search(line, pattern);
}

bool idFaces(std::string line, std::vector<int>& triangles)
{
// #TODO: clean this up
    std::istringstream iss(line);
    char prefix;
    iss >> prefix;
    if (!faceRegex(line)) return false;

    int num;
    std::string token;
    while (std::getline(iss, token, ' '))
    {
        std::istringstream fiss(token);
        std::string indexToken;
        while (std::getline(fiss, indexToken, '/'))
        {
            try {
                num = std::stoi(indexToken); // Convert token to integer
                triangles.push_back(num); // Add the integer to the triangle
            } catch (const std::invalid_argument& e) {
                // std::cerr << "Invalid argument: " << e.what() << std::endl;
                // Handle the error, e.g., ignore the token or abort the operation
            } catch (const std::out_of_range& e) {
                // std::cerr << "Out of range: " << e.what() << std::endl;
                // Handle the error, e.g., ignore the token or abort the operation
            }
        }

    }
    return true;
}

void MeshData::loadOBJ(const char *filePath) {
    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Error: Cannot open file " << filePath << std::endl;
    }
// TODO: write the rest of the function
    vertices.clear();
    uvs.clear();
    triangles.clear();

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> tokens;

        vec3 vertex;
        vec2 uv;
        if (vertRegex(line, vertex))
        {
            vertices.emplace_back(vertex);
        }
        else if (uvRegex(line, uv))
        {
            uvs.emplace_back(uv);
        }
        else if (idFaces(line, triangles))
        {

        }
    }
}