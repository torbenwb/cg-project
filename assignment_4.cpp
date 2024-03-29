// Torben Bernhard - Assignment 4
// Texture and Lights

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "GLXtras.h"
#include "VecMat.h"
#include "Camera.h"
#include "Draw.h"
#include "IO.h"
#include "Widgets.h"
#include "window.h"

GLFWwindow* w; // Window Reference
int screenWidth = 400, screenHeight = 400;
GLuint VBO = 0, VAO = 0, EBO = 0; // Vertex / Element Buffer ID
GLuint program = 0;		 // GLSL program ID
// Camera
Camera camera(0, 0, screenWidth, screenHeight, vec3(15, -30, 0), vec3(0, 0, -25), 30);

// Model Origin used for model translation
vec3 modelOrigin {0.0f, -1.0f, 0.0f};

// Texture
const char *textureFilename = "/Users/torbenbernhard/Desktop/Seattle U/cg-project/texture.jpg";
GLuint textureName = 0;
int textureUnit = 0;

// Lights
vec3 lights[] = {
        {0.5f, 0.0f, 1.5f},
        {1.0f, 1.0f, -1.5f}
};
const int nLights = sizeof(lights)/sizeof(vec3);
Mover mover; // used to move lights
void* picked = NULL;


// Shared vertex positions
float xFarLeft = -3.0f, xLeft = -1.0f, xRight = 1.0f, xFarRight = 3.0f;
float yLow = -1.0f, yMid = 1.0f, yTop = 3.0f;
float zFront = 1.0f, zBack = -1.0f;

// Letter Model vertices - changed name from points
vec3 vertices[]
{
    // Front
        {xLeft, yLow, zFront},{xLeft, yMid, zFront},
        {xFarLeft, yMid, zFront}, {xFarLeft, yTop, zFront},
        {xLeft, yTop, zFront}, {xRight, yTop, zFront},
        {xFarRight, yTop, zFront},{xFarRight, yMid, zFront},
        {xRight, yMid, zFront}, {xRight, yLow, zFront},
    // Back
        {xLeft, yLow, zBack},{xLeft, yMid, zBack},
        {xFarLeft, yMid, zBack}, {xFarLeft, yTop, zBack},
        {xLeft, yTop, zBack}, {xRight, yTop, zBack},
        {xFarRight, yTop, zBack},{xFarRight, yMid, zBack},
        {xRight, yMid, zBack}, {xRight, yLow, zBack}
};
// Triangle Indices
int triangles[][3]
{
    // Front Faces
{0, 1, 8}, {0, 8, 9}, {2, 4, 1},{2,3,4},
{1, 4, 5},{1, 5, 8},{8 ,5,6},{8, 6, 7},
    // Back Faces
{10, 11, 18},{10, 18, 19},{12, 14, 11}, {12, 13, 14},
{11, 14, 15},{11, 15, 18},{18, 15, 16},{18, 16, 17},
// Connecting Faces
{0, 10, 19},{0, 19, 9},{0, 1, 11},{0, 11, 10},
{2, 11, 1},{2, 12, 11},{2, 3, 13},{2, 13, 12},
{3, 13, 14},{3, 14, 4},{4, 14, 15},{4, 15, 5},
{5, 15, 16},{5, 16, 6},{7, 6, 16},{7, 16, 17},
{8, 18, 17},{8, 17, 7},{9,8, 18},{9, 18, 19}
};

// UVS for each vertex
vec2 uvs[]
{
        {0.33f,0.0f},{0.33f, 0.5f},
        {0.0f, 0.5f},{0.0f, 1.0f},
        {0.33f, 1.0f},{0.66f, 1.0f},
        {1.0f, 1.0f}, {1.0f, 0.5f},
        {0.66f, 0.5f},{0.66f, 0.0f},
        //
        {0.33f,0.0f},{0.33f, 0.5f},
        {0.0f, 0.5f},{0.0f, 1.0f},
        {0.33f, 1.0f},{0.66f, 1.0f},
        {1.0f, 1.0f}, {1.0f, 0.5f},
        {0.66f, 0.5f},{0.66f, 0.0f}
};

void SetUvs()
{
    int nPoints = sizeof(vertices)/sizeof(vec3);
    vec3 min, max;
    Bounds(vertices, nPoints, min, max);
    vec3 dif(max - min);
    for(int i = 0; i < nPoints; i++)
    {
        float x = vertices[i].x;
        float y = vertices[i].y;
        uvs[i] = vec2((x-min.x)/dif.x, (y-min.y)/dif.y);
    }
}

/*
 * Vertex Shader
 */
const char *vertexShader = R"(
	#version 330 core
    uniform mat4 modelview, persp;
	in vec3 point;
	in vec2 uv;
	out vec2 vUv;
    out vec3 vPoint;
	void main() {
        vPoint = (modelview * vec4(point, 1)).xyz;
		gl_Position = persp * vec4(vPoint, 1);
		vUv = uv;
	}
)";

/*
 * Pixel Shader
 */
const char *pixelShader = R"(
	#version 330 core
	in vec2 vUv;
    in vec3 vPoint;
    uniform int nLights = 0;
    uniform vec3 lights[20];
    uniform sampler2D textureImage;

	out vec4 pColor;
    uniform float amb = .1, dif = .7, spc = .4;
    vec3 N;
    vec3 L;
    vec3 R;
    float d = 0;
    float h;
    float s = 0;

	void main() {
        float intensity = 0.0;
        vec3 dx = dFdx(vPoint), dy = dFdy(vPoint);
        vec3 N = normalize(cross(dx, dy));
        vec3 E = normalize(vPoint);

        for(int i = 0; i < nLights; i++)
        {
            vec3 L = normalize(lights[i]-vPoint);
            d += abs(dot(N,L));

            vec3 R = reflect(L, N);
            float h = max(0, dot(R, E));
            s += pow(h, 100);
        }

        intensity = min(1, amb+dif*d)+spc*s;
        vec3 col = texture(textureImage, vUv).rgb;

        pColor = vec4(intensity*col,1);
	}
)";

/*
 * Display model to screen
 * - Clear Background
 * - Enable Depth Test
 * - Buffer Vertices
 * -
 */
void Display() {
    vec3 xLights[nLights];
    for(int i = 0; i < nLights; i++) {
        xLights[i] = Vec3(camera.modelview*vec4(lights[i], 1));
    }

    // Clear background
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    // Enable Depth Test
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // Access GPU vertex buffer
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Associate position input to shader with position array in vertex buffer
    VertexAttribPointer(program, "point", 3, 0, (void *) 0);
    // UVs
    VertexAttribPointer(program, "uv", 2, 0, (void*)sizeof(vertices));
    // Translate using modelOrigin and camera rotation / position
    mat4 modelView = camera.modelview * Translate(modelOrigin);
    // Set Uniforms
    SetUniform(program, "modelview", modelView);
    SetUniform(program, "persp", camera.persp);
    SetUniform(program, "textureImage", textureUnit);

    glBindTexture(GL_TEXTURE_2D, textureName);
    glActiveTexture(GL_TEXTURE0+textureUnit);

    // Update Lights
    SetUniform(program, "nLights", nLights);
    SetUniform3v(program, "lights", nLights, (float*)xLights);

    // Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Draw Elements
    int trianglesCount = sizeof (triangles)/sizeof (int);
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, 0);
    glDisable(GL_DEPTH_TEST);

    // Draw light positions
    /*
    UseDrawShader(camera.fullview);
    for(int i = 0; i < nLights; i++)
    {
        Star(lights[i], 8, vec3(1,0.8f,0), vec3(0, 0, 1));
    }
    */
    glFlush();
}

/*
 * Buffer Vertices
 */
void BufferVertices() {
    // make GPU buffer for points and colors, set it active buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // allocate buffer memory to hold vertex locations and colors
    int sPoints = sizeof(vertices);
    int sUvs = sizeof(uvs);
    glBufferData(GL_ARRAY_BUFFER, sPoints + sUvs, NULL, GL_STATIC_DRAW);
    // load data to the GPU
    glBufferSubData(GL_ARRAY_BUFFER, 0, sPoints, vertices);
    // start at beginning of buffer, for length of points array
    // glBufferSubData(GL_ARRAY_BUFFER, sPoints, sColors, colors);
    // start at end of points array, for length of uvs array
    glBufferData(GL_ARRAY_BUFFER, sPoints+sUvs, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sPoints, sUvs, uvs);

    // Fill Element Buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
}

void WriteOBJFile(const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file)
    {
        int nPoints = sizeof(vertices)/sizeof(vec3);
        int nTris = sizeof(triangles)/(sizeof(int)*3);

        fprintf(file, "\n# %i vertices\n", nPoints);
        for(int i = 0; i < nPoints; i++)
        {
            fprintf(file, "v %f %f %f \n", vertices[i].x, vertices[i].y, vertices[i].z);
        }
        fprintf(file, "\n# %i textures\n", nPoints);
        for(int i = 0; i < nPoints; i++)
        {
            fprintf(file, "vt %f %f \n", uvs[i].x, uvs[i].y);
        }
        fprintf(file, "\n# %i triangles\n", nTris);
        for(int i = 0; i < nTris; i++)
        {
            fprintf(file, "# f %i %i %i \n",
                    1+triangles[i][0], 1+triangles[i][1], 1+triangles[i][2]);
        }
        fclose(file);
    }
    else
    {
        printf("Cannot open file");
    }
}

/*
 *  Mouse Button Callback
 *  Used to track whether the left mouse button is currently pressed down.
 */
void MouseButton(float x, float y, bool left, bool down)
{
    if (left && down)
    {
        picked = NULL;
        for(int i = 0; i < nLights; i++)
        {
            if (MouseOver(x, y, lights[i], camera.fullview))
            {
                picked = &mover;
                mover.Down(&lights[i], (int)x,(int)y, camera.modelview, camera.persp);
            }
        }
        if (picked == NULL)
        {
            picked = &camera;
            camera.Down(x, y, Shift(), Control());
        }
    }
    else
    {
        camera.Up();
    }
}
/*
 * Mouse Move Callback
 * Used to update X axis and Y axis rotation values based on mouse position.
 * Only updates rotation when mouse is held down.
 */
void MouseMove(float x, float y, bool leftDown, bool rightDown) {

    if (leftDown)
    {
        if (picked == &mover)
        {
            mover.Drag((int)x,(int)y, camera.modelview, camera.persp);
        }
        if (picked == &camera)
        {
            camera.Drag(x, y);
        }
    }
}
/*
 * Mouse Wheel Callback
 * Connects user mouse wheel input to camera.Wheel()
 */
void MouseWheel(float spin)
{
    camera.Wheel(spin, Shift());
}
/*
 * Resize
 * Called when GLFW window is resized.
 * Connected to camera.Resize()
 */
void Resize(int width, int height)
{
    camera.Resize(width, height);
}


// Main Application
int main() {
    //WriteOBJFile("/Users/torbenbernhard/Desktop/Seattle U/cg-project/t.obj");
    w = initWindow(0, 0,500, 500, "title");
    // Create Shader Program
    program = LinkProgramViaCode(&vertexShader, &pixelShader);
    if (!program) {
        printf("can't init shader program\n");
        getchar();
        return 0;
    }
    // Register Mouse Callbacks
    // RegisterMouseButton(MouseButton);
    // RegisterMouseMove(MouseMove);
    // RegisterMouseWheel(MouseWheel);

    // Register Resize Callback
    // RegisterResize(Resize);

    // Load Texture from file
    //textureName = ReadTexture(textureFilename);

    // Set UVS
    SetUvs();

    // Allocate vertex memory in the GPU
    BufferVertices();
    // Event loop
    glfwSwapInterval(1); // ensure no generated frame backlog
    while (!glfwWindowShouldClose(w)) {

        Display();
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
    // unbind vertex buffer, free GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(w);
    glfwTerminate();
}
