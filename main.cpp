
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
            math::random::randomInt(15, 25),
            math::random::randomInt(15, 25),
            math::random::randomInt(15, 25),
            2,
            math::random::randomDouble(1.5, 2.5),
            math::random::randomDouble(1.5, 2.5),
            true
    );
    Voxel::World::worldSeed = newWorldSeed;

    OGL::Transform viewTransform;
    glm::vec3 lookRotationEuler;
    math::Projection projection(1.0f, 1.0f, 0.01f, 1000.0f);
    OGL::Scene scene;


    Voxel::ChunkLoader chunkLoader(&voxelMaterial, &scene);

    while(!window.getShouldClose())
    {
        updateView(viewTransform, lookRotationEuler);

        scene.render(viewTransform.getMatrix(), projection.getMatrix());

        glm::vec3 chunkOrigin = getChunkOrigin(viewTransform.position);
        std::vector<glm::vec3> chunkArea = Voxel::ChunkLoader::getChunkArea(chunkOrigin, 4);
        chunkLoader.queueChunkArea(chunkArea);
        chunkLoader.setCurrentArea(chunkArea);
        chunkLoader.update();


        window.update();
    }
    window.close();
    return 0;
}
