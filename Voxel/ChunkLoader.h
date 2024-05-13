//
// Created by Torben Bernhard on 5/11/24.
//

#ifndef CG_PROJECT_CHUNKLOADER_H
#define CG_PROJECT_CHUNKLOADER_H

#include <vector>
#include "Chunk.h"
#include "../OGL/Mesh.h"
#include "../OGL/MeshData.h"
#include "../OGL/MeshRenderer.h"
#include "../OGL/Material.h"
#include "../OGL/Scene.h"

namespace Voxel
{
    class ChunkLoader {
    private:
        std::vector<Voxel::Chunk> loadedChunks;
        std::vector<unsigned int> loadedChunkMeshRenderIds;
        OGL::Material* material;
        OGL::Scene* scene;
        std::vector<glm::vec3> loadQueue;
        std::vector<glm::vec3> currentArea;

    public:
        ChunkLoader(OGL::Material* _material, OGL::Scene* _scene): material(_material), scene(_scene){}
        void loadChunk(glm::vec3 origin);
        void unloadChunk(glm::vec3 origin);
        void loadChunkArea(std::vector<glm::vec3> origins);
        void unloadChunkArea(std::vector<glm::vec3> origins);
        void queueChunk(glm::vec3 origin);
        void queueChunkArea(std::vector<glm::vec3> origins);
        bool isChunkLoaded(glm::vec3 origin);
        bool isChunkInCurrentArea(glm::vec3 origin);
        void setCurrentArea(std::vector<glm::vec3> area);
        void update();

        static std::vector<glm::vec3> getChunkArea(glm::vec3 origin, int distance);

    };
}



#endif //CG_PROJECT_CHUNKLOADER_H
