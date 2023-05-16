#include "raylib.h"
#include "raymath.h"

bool CheckCollisionRayBox(Ray ray, BoundingBox box)
{
    float tmin = -INFINITY, tmax = INFINITY;
    Vector3 invDir = { 1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z };
    Vector3 bounds[2] = { box.min, box.max };

    for (int i = 0; i < 3; i++) {
        float t1 = (bounds[ray.direction.x < 0 ? 1 : 0].x - ray.position.x) * invDir.x;
        float t2 = (bounds[1 - (ray.direction.x < 0 ? 1 : 0)].x - ray.position.x) * invDir.x;
        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));

        t1 = (bounds[ray.direction.y < 0 ? 1 : 0].y - ray.position.y) * invDir.y;
        t2 = (bounds[1 - (ray.direction.y < 0 ? 1 : 0)].y - ray.position.y) * invDir.y;
        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));

        t1 = (bounds[ray.direction.z < 0 ? 1 : 0].z - ray.position.z) * invDir.z;
        t2 = (bounds[1 - (ray.direction.z < 0 ? 1 : 0)].z - ray.position.z) * invDir.z;
        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));
    }

    return tmax >= tmin;
}

//Define a struct to represent a cube
struct Cube {
    Vector3 position;
    Color color;
};

bool isCubeVisible(Camera camera, Cube cube, Cube cubes[], int numCubes) {
    // Check if the cube is in the view of the camera
    Vector2 cubeScreenPos = GetWorldToScreen(cube.position, camera);
    if (cubeScreenPos.x < 0 || cubeScreenPos.x > GetScreenWidth() || cubeScreenPos.y < 0 || cubeScreenPos.y > GetScreenHeight()) {
        return false;
    }  
    // Cube is visible
    return true;
}

bool Vector3IsEqual(Vector3 v1, Vector3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

int main() {
    // Initialize raylib
    InitWindow(800, 450, "Occlusion Culling Example");

    // Initialize the camera
    Camera camera = { 0 };
    camera.position = { 30.0f, 30.0f, 30.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Initialize the cubes
    const int numCubes = 100;
    Cube cubes[numCubes];
    for (int i = 0; i < numCubes; i++) {
        cubes[i].position = { (float)GetRandomValue(-20, 20), (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100) };
        cubes[i].color = { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
    }

    // Store the camera's previous position and rotation
    Vector3 prevCameraPos = camera.position;
    Vector3 prevCameraTarget = camera.target;

    int visibleCubes = 0 ; 
    int frameCounter = 0 ;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        visibleCubes = 0 ;
        frameCounter++;
        if(frameCounter > 120){
            frameCounter = 0 ;
        }
        BeginDrawing();
            // Clear the screen
            ClearBackground(RAYWHITE);

            //
            BeginMode3D(camera);

                DrawGrid(10, 1.0f);

                // Draw the cubes that are visible to the camera
                for (int i = 0; i < numCubes; i++) {
                    if (isCubeVisible(camera, cubes[i], cubes, numCubes)) {
                        if(cubes[i].color.a < 255){
                            if(frameCounter % 60 == 0 ){
                                cubes[i].color.a = cubes[i].color.a + 1;
                            }
                        }

                        visibleCubes += 1;
                        DrawCube(cubes[i].position, 1.0f, 1.0f, 1.0f, cubes[i].color);
                    } else {
                        cubes[i].color.a = 0;
                    }
                }

            // End drawing
            EndMode3D();

            DrawText(TextFormat("visible CUbes: %d", visibleCubes), 10, 30, 20, BLACK);
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
