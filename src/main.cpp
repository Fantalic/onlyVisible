#include "raylib.h"
#include "raymath.h"
#include "PerlinNoise.h"
#include "Cube.h"

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

bool Vector3IsEqual(Vector3 v1, Vector3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

int main() {

    PerlinNoise pn(rand() % UINT_MAX);

    // Initialize raylib
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800*2, 450*2, "Occlusion Culling Example");
    
    // Initialize the camera
    Camera camera = { 0 };
    camera.position = { 30.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Initialize the cubes
    const float cubeSize = 0.5f;
    const int numCubes = 10000;
    std::vector<Cube> cubes;
    // for (int i = 0; i < numCubes; i++) {
    //     cubes[i].position = { (float)GetRandomValue(-20, 20), (float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100) };
    //     cubes[i].color = { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
    // }

    std::vector<std::vector<double>> terrainGraph = pn.generate3DGraph(100);

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {

            //TODO: round the z value to int
            double nf = terrainGraph[x][y];
            int z = (int)std::round(nf * 100 - 50);

            Vector3 pos = (Vector3){x*cubeSize,z*cubeSize,y*cubeSize};

            Cube cube = Cube();
            cube.position = pos;
            // cube.color = { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
            cube.color = { (unsigned char)GetRandomValue(0, 255), (unsigned char)(int)std::round(100*nf), (unsigned char)(int)std::round(255*nf), 255 };
            
            cubes.push_back(cube);
        }
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

                // #################################
                // make a grid, so don't have to iterate all objects in the world, but only the ones that are in the view of the camera
                // there will be an 3d array representing the space and the items in it. Each elemnt holds an instance of an element.
                // the class holds a render function, that starts rendering the object when its in the view of the camera.
                // the grid holds points of the objects mesh. representing the edges of the mesh 
                // if  
                // how has the grid has to look ? how big are its pieces ? 
                // maybe they 
                // ##################################


                // Draw the cubes that are visible to the camera
                for (Cube cube : cubes) {
                    if (cube.isCubeVisible(camera)) {
                        //fade-in effect
                        if(cube.color.a < 255){
                            if(frameCounter % 1 == 0 ){
                                cube.color.a = cube.color.a + 1;
                            }
                        }

                        visibleCubes += 1;
                        DrawCube(cube.position, cubeSize, cubeSize, cubeSize, cube.color);
                    } else {
                        cube.color.a = 0;
                    }
                }

            // End drawing
            EndMode3D();

            DrawText(TextFormat("visible CUbes: %d", visibleCubes), 10, 30, 20, BLACK);
            DrawText(TextFormat("test: %d", terrainGraph[50][50]), 10, 50, 20, BLACK);
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
