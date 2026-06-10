#ifndef CUBE_H
#define CUBE_H

#include <raylib.h>

constexpr float CUBE_SIZE = 0.5f;

const Vector3 cubeVertices[8] = {
    { -0.5f, -0.5f, -0.5f }, // 0: Back bottom left
    {  0.5f, -0.5f, -0.5f }, // 1: Back bottom right
    {  0.5f,  0.5f, -0.5f }, // 2: Back top right
    { -0.5f,  0.5f, -0.5f }, // 3: Back top left
    { -0.5f, -0.5f,  0.5f }, // 4: Front bottom left
    {  0.5f, -0.5f,  0.5f }, // 5: Front bottom right
    {  0.5f,  0.5f,  0.5f }, // 6: Front top right
    { -0.5f,  0.5f,  0.5f }  // 7: Front top left
};

// Define the triangles for each face (two triangles per face)
const int cubeFaces[6][6] = {
    {0, 1, 2,   2, 3, 0}, // Back face
    {4, 6, 5,   4, 7, 6}, // Front face
    {4, 5, 1,   4, 1, 0}, // Bottom face
    {3, 2, 6,   3, 6, 7}, // Top face
    {7, 6, 2,   7, 2, 3}, // Left face
    {1, 5, 6,   1, 6, 2}   // Right face
};

class Cube
{
    public:
        Cube();
        ~Cube();

        Vector3 position;
        Color color;
        double size=0.5f;

        bool IsFaceVisible(Camera camera, int faceIndex);
        bool isCubeVisible(Camera camera);

};

#endif