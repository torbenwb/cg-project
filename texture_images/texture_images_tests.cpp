//
// Created by Torben Bernhard on 4/27/24.
//
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "atlas.h"

bool testAtlasGetUVs();

int main()
{
    printf("Run Texture Image Tests\n");
    testAtlasGetUVs();
    return 0;
}

bool testAtlasGetUVs()
{
    int width = 2, height = 2;
    std::vector<glm::vec2> testUVS;

    texture_images::atlas::getUVs(1, 1, width, height, testUVS);
    for(int i = 0; i < testUVS.size(); i++)
    {
        printf("(%f,%f)", testUVS[i].x, testUVS[i].y);
    }
    return true;
}