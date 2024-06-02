//
// Created by Torben Bernhard on 5/11/24.
//

#include "ChunkLoader.h"

namespace Voxel
{
    void ChunkLoader::loadChunk(glm::vec3 origin) {
        if (isChunkLoaded(origin)) return;
        loadedChunks.emplace_back(Chunk::generateChunk(origin));
        unsigned int meshRendererId = scene->addMeshRenderer(
                loadedChunks.back().mesh->getMeshData(),
                material->getShaderProgram(),
                OGL::Transform(origin)
        );
        loadedChunkMeshRenderIds.emplace_back(meshRendererId);
    }

    void ChunkLoader::unloadChunk(glm::vec3 origin) {
        if (!isChunkLoaded(origin)) return;
        int eraseIndex = -1;
        for(int i = 0; i < loadedChunks.size(); i++){
            if (loadedChunks[i].origin == origin) {
                eraseIndex = i;
                break;
            }
        }
        scene->removeMeshRenderer(loadedChunkMeshRenderIds[eraseIndex]);

        loadedChunks.erase(loadedChunks.begin() + eraseIndex);
        loadedChunkMeshRenderIds.erase(loadedChunkMeshRenderIds.begin() + eraseIndex);
    }

    void ChunkLoader::unloadChunkArea(std::vector<glm::vec3> origins) {
        for(auto origin : origins){
            unloadChunk(origin);
        }
    }

    void ChunkLoader::loadChunkArea(std::vector<glm::vec3> origins) {
        for(auto origin : origins)
        {
            if (!isChunkLoaded(origin)){
                loadChunk(origin);
            }
        }
    }

    bool ChunkLoader::isChunkLoaded(glm::vec3 origin) {
        for(auto chunk : loadedChunks){
            if (chunk.origin == origin) return true;
        }
        return false;
    }

    std::vector<glm::vec3> ChunkLoader::getChunkArea(glm::vec3 origin, int distance) {
        std::vector<glm::vec3> area;

        for(int x = -distance; x <= distance; x++){
            for(int z = -distance; z <= distance; z++){

                glm::vec3 p = glm::vec3(origin.x + (x * 32.0), 0, origin.z + (z * 32.0));
                //printf("Get Chunk Area: x: %d, z: %d, p = (%f, %f, %f)\n", x, z, p.x, p.y, p.z);
                area.emplace_back(p);
            }
        }
        return area;
    }

    void ChunkLoader::update() {
        for(auto chunk : loadedChunks){
            if (!isChunkInCurrentArea(chunk.origin)){
                unloadChunk(chunk.origin);
                break;
            }
        }

        if (loadQueue.size() > 0)
        {
            auto next = loadQueue.back();
            if (!isChunkLoaded(next) && isChunkInCurrentArea(next)) loadChunk(next);
            loadQueue.pop_back();
        }


    }

    void ChunkLoader::queueChunk(glm::vec3 origin) {
        if (!isChunkLoaded(origin)) loadQueue.emplace_back(origin);
    }

    void ChunkLoader::queueChunkArea(std::vector<glm::vec3> origins) {
        for(auto origin: origins)
        {
            if (!isChunkLoaded(origin)) loadQueue.emplace_back(origin);
        }
    }

    void ChunkLoader::setCurrentArea(std::vector<glm::vec3> area) {
        this->currentArea = area;
    }

    bool ChunkLoader::isChunkInCurrentArea(glm::vec3 origin) {
        for(int i = 0; i < currentArea.size(); i++){
            if (currentArea[i] == origin) return true;
        }
        return false;
    }

    void ChunkLoader::reloadChunk(glm::vec3 origin) {
        unloadChunk(origin);
        loadChunk(origin);
    }

}

