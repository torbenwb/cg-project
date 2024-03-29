//
// Created by Torben Bernhard on 3/28/24.
//

#ifndef CG_PROJECT_MESHDATA_H
#define CG_PROJECT_MESHDATA_H

#include <vector>
#include "VecMat.h"

class MeshData
{
public:
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec3> colors;
    std::vector<vec2> uvs;
    std::vector<int> triangles;

    void loadOBJ(const char* filePath);
};

bool vertRegex(std::string line, vec3& result);

bool uvRegex(std::string line, vec2& result);

bool faceRegex(std::string line);

bool idFaces(std::string line, std::vector<int>& triangles);

#endif //CG_PROJECT_MESHDATA_H
