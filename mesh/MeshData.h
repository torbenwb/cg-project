//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_MESHDATA_H
#define CG_PROJECT_MESHDATA_H

#include <vector>
#include <glm/glm.hpp>

namespace Mesh
{
    struct triangle;
    struct MeshData;

    struct triangle{
        int a, b, c;
        triangle(int a, int b, int c){
            this->a = a;
            this->b = b;
            this->c = c;
        }
    };

    struct MeshData
    {
    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<triangle> triangles;
    public:
        void addVertex(glm::vec3 vertex) {
            this->vertices.emplace_back(vertex);
        }
        void addVertices(std::vector<glm::vec3> vertices) {
            for(auto v : vertices){
                this->vertices.emplace_back(v);
            }
        }
        void setVertices(std::vector<glm::vec3> vertices){
            this->vertices = vertices;
        }
        void addNormal(glm::vec3 normal){
            this->normals.emplace_back(normal);
        }
        void addNormals(std::vector<glm::vec3> normals){
            for(auto n : normals){
                this->normals.emplace_back(n);
            }
        }
        void setNormals(std::vector<glm::vec3> normals){
            this->normals = normals;
        }
        void addUV(glm::vec2 uv){
            this->uvs.emplace_back(uv);
        }
        void addUVs(std::vector<glm::vec2> uvs){
            for(auto uv : uvs){
                this->uvs.emplace_back(uv);
            }
        }
        void setUVs(std::vector<glm::vec2> uvs){
            this->uvs = uvs;
        }
        void addTriangle(triangle t){
            this->triangles.emplace_back(t);
        }
        void addTriangles(std::vector<triangle> triangles){
            for(auto t : triangles){
                this->triangles.emplace_back(t);
            }
        }
        void setTriangles(std::vector<triangle> triangles){
            this->triangles = triangles;
        }
    };
}

#endif //CG_PROJECT_MESHDATA_H

