
#include "open_gl/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include "input.h"
#include "OGL/Scene.h"
#include "OGL/Mesh.h"
#include "OGL/Transform.h"
#include "OGL/Material.h"
#include "projection.h"
#include "Voxel/World.h"
#include "Voxel/Chunk.h"
#include "Voxel/ChunkLoader.h"
#include "math/random.h"
#include <cmath>

void updateView(OGL::Transform& viewTransform, glm::vec3& lookRotationEuler)
{
    const float MOVE_SPEED = 1.0f;
    glm::vec3 forward = viewTransform.getForward();
    glm::vec3 right = viewTransform.getRight();

    float x = open_gl::Input::getAxis(GLFW_KEY_D, GLFW_KEY_A);
    float y = open_gl::Input::getAxis(GLFW_KEY_W, GLFW_KEY_S);
    float z = open_gl::Input::getAxis(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);

    float lookX = open_gl::Input::getMouseX();
    float lookY = open_gl::Input::getMouseY();

    // Adjust the rotation based on mouse input
    lookRotationEuler.x += lookY * 0.1f;
    lookRotationEuler.y += lookX * 0.1f;

    glm::vec3 pitchAxis = glm::vec3(1, 0, 0);
    glm::vec3 yawAxis = glm::vec3(0, 1, 0);
    // Calculate rotation quaternions
    glm::quat pitch = glm::angleAxis(glm::radians(lookRotationEuler.x), pitchAxis);
    glm::quat yaw = glm::angleAxis(glm::radians(lookRotationEuler.y), yawAxis);

    glm::quat q = pitch;
    q *= yaw;
    glm::quat combinedRotation = q;

    // Calculate movement direction
    glm::vec3 moveDirection = forward * y + right * x;
    moveDirection.y -= z;

    // Update position and rotation
    viewTransform.position += moveDirection * MOVE_SPEED;
    viewTransform.rotation = combinedRotation;

    if (open_gl::Input::getKey(GLFW_KEY_ESCAPE)) open_gl::Input::enableCursor();
}


glm::vec3 getChunkOrigin(glm::vec3 worldPosition) {
    const int WIDTH = Voxel::Chunk::WIDTH;
    const int HEIGHT = Voxel::Chunk::HEIGHT;
    int globalX = worldPosition.x;
    int globalY = worldPosition.y;
    int globalZ = worldPosition.z;
    int x = globalX >= 0 ? (globalX / WIDTH) * WIDTH : ((globalX / WIDTH) - 1) * WIDTH;
    int y = (globalY / HEIGHT) * HEIGHT;
    int z = globalZ >= 0 ? (globalZ / WIDTH) * WIDTH : ((globalZ / WIDTH) - 1) * WIDTH;
    x = -x - WIDTH;
    y = 0;
    z = -z - WIDTH;
    return {x, y, z};
}

 OGL::Mesh* voxel(unsigned short type){
    std::vector<glm::vec3> verts;
    std::vector<glm::vec2> uvs;
    std::vector<int> tris;

    unsigned short vType = type;
    Voxel::Chunk::topFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    Voxel::Chunk::bottomFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    Voxel::Chunk::leftFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    Voxel::Chunk::rightFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    Voxel::Chunk::frontFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    Voxel::Chunk::backFace(vType, glm::vec3(0.0f, 0.0f, 0.0f), verts,tris, uvs);
    return new OGL::Mesh(verts, uvs, tris);
}

int main()
{

    open_gl::Window window;
    window.open();
    open_gl::Input::registerCallbacks();
    open_gl::Input::disableCursor();


    OGL::Material voxelMaterial(
            "/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/shaders/standardVertexShader.vs",
            "/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/shaders/standardFragmentShader.fs",
            "/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/pixil-frame-0.png"
            );
    voxelMaterial.compile();

    Voxel::WorldSeed newWorldSeed = Voxel::WorldSeed(
            math::random::randomInt(15, 30),
            math::random::randomInt(15, 30),
            math::random::randomInt(15, 30),
            2,
            math::random::randomDouble(1.5, 2.5),
            math::random::randomDouble(1.5, 2.5),
            true
    );
    Voxel::World::worldSeed = newWorldSeed;

    OGL::Transform viewTransform;
    OGL::Transform cubeTransform;
    OGL::Transform cube2Transform;
    glm::vec3 lookRotationEuler;
    math::Projection projection(1.0f, 1.0f, 0.01f, 1000.0f);
    OGL::Scene scene;


    Voxel::ChunkLoader chunkLoader(&voxelMaterial, &scene);
    unsigned char placeVoxelType = Voxel::World::VOXEL_TYPE_STONE;
    OGL::Mesh* cubeMesh = voxel(placeVoxelType);
    unsigned int cubeIndex = scene.addMeshRenderer(cubeMesh->getMeshData(), voxelMaterial.getShaderProgram(), cubeTransform);
    //unsigned int cubeTwo = scene.addMeshRenderer(cubeMesh->getMeshData(), voxelMaterial.getShaderProgram(), cube2Transform);
    glm::vec3 targetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cube2Position = glm::vec3(0.0f, 0.0f, 0.0f);



    bool leftMouseDown;
    bool rightMouseDown;

    while(!window.getShouldClose())
    {


        updateView(viewTransform, lookRotationEuler);
        float y = viewTransform.position.y;
        float x = viewTransform.position.x;
        float z = viewTransform.position.z;
        targetPosition.y = -y;
        targetPosition.x = -x;
        targetPosition.z = -z;
        targetPosition += viewTransform.getForward() * -5.0f;

        targetPosition.x = round(targetPosition.x);
        targetPosition.y = round(targetPosition.y);
        targetPosition.z = round(targetPosition.z);
        cubeTransform.position = targetPosition;
        //printf("view position: (%f, %f, %f), cube position: (%f, %f, %f)\n", viewTransform.position.x, viewTransform.position.y, viewTransform.position.z, cubeTransform.position.x, cubeTransform.position.y, cubeTransform.position.z);
        scene.updateMeshRendererTransform(cubeIndex, cubeTransform);



        scene.render(viewTransform.getMatrix(), projection.getMatrix());

        glm::vec3 chunkOrigin = getChunkOrigin(viewTransform.position);
        std::vector<glm::vec3> chunkArea = Voxel::ChunkLoader::getChunkArea(chunkOrigin, 2);

        if (open_gl::Input::getKey(GLFW_KEY_0)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_EMPTY;
            scene.setMeshRendererActive(cubeIndex, false);
        }
        if (open_gl::Input::getKey(GLFW_KEY_1)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_GRASS;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_2)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_WATER;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_3)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_SAND;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_4)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_STONE;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_5)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_WOOD;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_6)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_LEAVES;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }
        if (open_gl::Input::getKey(GLFW_KEY_7)) {
            placeVoxelType = Voxel::World::VOXEL_TYPE_DIRT;
            delete cubeMesh;
            cubeMesh = voxel(placeVoxelType);
            scene.updateMeshRendererMeshData(cubeIndex, cubeMesh->getMeshData());
            scene.setMeshRendererActive(cubeIndex, true);
        }

        if (open_gl::Input::getMouseLeft()) leftMouseDown = true;
        else if (leftMouseDown) {
            Voxel::World::setVoxelType(targetPosition.x, targetPosition.y, targetPosition.z, placeVoxelType);
            for(auto origin : chunkArea){
                chunkLoader.reloadChunk(origin);
            }
        }
        if (!open_gl::Input::getMouseLeft()) leftMouseDown = false;

        if (open_gl::Input::getMouseRight()) rightMouseDown = true;
        else if (rightMouseDown){
            Voxel::World::setVoxelType(targetPosition.x, targetPosition.y, targetPosition.z, Voxel::World::VOXEL_TYPE_EMPTY);
            for(auto origin : chunkArea){
                chunkLoader.reloadChunk(origin);
            }
        }
        if (!open_gl::Input::getMouseRight()) rightMouseDown = false;


        chunkLoader.queueChunkArea(chunkArea);
        chunkLoader.setCurrentArea(chunkArea);
        chunkLoader.update();

        int width, height;
        window.getWindowSize(&width, &height);
        projection.aspectRatio = (double)width / (double)height;
        window.update();
    }
    window.close();
    return 0;
}
