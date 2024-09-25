#include "raylib.h"
#include "Cube.h"

Cube::Cube()
    : position{ 0.0f, 0.0f, 0.0f }
    , color{ 255, 255, 255, 255 }
    , size{ 0.5f }
{}

Cube::~Cube() {}

bool Cube::isCubeVisible(Camera camera) {
    // Check if the cube is in the view of the camera
    Vector2 cubeScreenPos = GetWorldToScreen(this->position, camera);
    if (cubeScreenPos.x < 0 || cubeScreenPos.x > GetScreenWidth() || cubeScreenPos.y < 0 || cubeScreenPos.y > GetScreenHeight()) {
        this->color.a = 0;
        return false;
    }  
    // Cube is visible
    return true;
}

bool Cube::IsFaceVisible(Camera camera, int faceIndex) {
    Vector3 faceNormal;
    
    switch (faceIndex) {
        case 0: faceNormal = (Vector3){0.0f, 0.0f, -1.0f}; break; // Back face
        case 1: faceNormal = (Vector3){0.0f, 0.0f, +1.0f}; break; // Front face
        case 2: faceNormal = (Vector3){0.0f, -1.0f, 0.0f}; break; // Bottom face
        case 3: faceNormal = (Vector3){0.0f, +1.0f, 0.0f}; break; // Top face
        case 4: faceNormal = (Vector3){-1.0f, 0.0f, +1.0f}; break; // Left face
        case 5: faceNormal = (Vector3){+1.0f, +1.0f , +1.0f}; break; // Right face
        default: return false;
    }

    // Vector3 toCube = Vector3Subtract(this->position, camera.position);
    
    // return Vector3DotProduct(toCube ,faceNormal) > 0;
    return true;
}