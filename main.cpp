#include "open_gl/window.h"
#include "open_gl/mesh.h"
#include "open_gl/shaderLib.h"
#include "open_gl/scene.h"
#include "open_gl/voxel.h"
#include "math/transform.h"
#include "math/projection.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "input.h"


void updateView(math::Transform& viewTransform, glm::vec3& lookRotationEuler)
{
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
    viewTransform.position += moveDirection * 0.1f;
    viewTransform.rotation = combinedRotation;

    if (open_gl::Input::getKey(GLFW_KEY_ESCAPE))
        open_gl::Input::enableCursor();

}

open_gl::Scene scene;

int main()
{
    open_gl::Window window;
    window.open();
    open_gl::Input::registerCallbacks();
    open_gl::Input::disableCursor();

    // Transforms
    float yaw = 0.0f, roll = 0.0f, pitch = 0.0f;
    glm::vec3 lookRotationEuler;
    math::Transform model;
    model.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    model.position = glm::vec3(0.f, 0.0f, 0.0f);

    math::Transform view;
    view.position = glm::vec3(0.0f, 0.0f, -5.0f);
    view.rotation = glm::quat(glm::vec3(0.0f, yaw, 0.0f));

    math::Projection projection(1.0f, 1.0f, 0.01f, 1000.0f);

    GLuint vertexShader = open_gl::compileShader("/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/shaders/standardVertexShader.vs", GL_VERTEX_SHADER);
    GLuint fragmentShader = open_gl::compileShader("/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/shaders/standardFragmentShader.fs", GL_FRAGMENT_SHADER);
    GLuint shaderProgram = open_gl::linkShaderProgram(vertexShader, fragmentShader);
    const char* atlasfp = "/Users/torbenbernhard/Desktop/Seattle U/Spring Quarter 2024/Graphics Project/cg-project/pixil-frame-0.png";
    GLuint textureId = open_gl::bufferTextureFromFile(atlasfp, true);

    // Get the uniform location of the texture sampler
    GLint textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");

    // Set the active texture unit and bind the texture to it
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set the value of the uniform to the texture unit index
    glUniform1i(textureLocation, 0); // 0 is the texture unit index

    std::vector<open_gl::Mesh*> chunkMeshes;
    std::vector<math::Transform> chunkTransforms;
    for(int x = -1; x <= 1; x++)
    {
        for(int z = -1; z <= 1; z++)
        {
            chunkMeshes.emplace_back(open_gl::voxel::generateChunkMesh(x * open_gl::voxel::width, z * open_gl::voxel::width));
            chunkTransforms.emplace_back(math::Transform(glm::vec3(x * open_gl::voxel::width, 0, z * open_gl::voxel::width)));
        }
    }

    for(int i = 0; i < chunkMeshes.size(); i++)
    {
        scene.addMeshRenderer(chunkMeshes[i], &chunkTransforms[i], shaderProgram);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);


    while(!window.getShouldClose())
    {
        updateView(view, lookRotationEuler);

        scene.setView(view.getMatrix());
        scene.setProjection(projection.getMatrix());
        scene.render();

        window.update();
    }
    window.close();
    return 0;
}