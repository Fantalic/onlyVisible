#include "raylib.h"
#include "raymath.h"
#include "PerlinNoise.h"
#include "Cube.h"
#include <cmath>

int main() {

    unsigned int seed = 21; //rand() % UINT_MAX;
    PerlinNoise pn(seed);

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
    std::vector<Cube> cubes;

    int terrainSize = 400;
    std::vector<std::vector<double>> terrainGraph = pn.smoothGraph( pn.generate3DGraph(terrainSize), 5);
    // std::vector<std::vector<double>> terrainGraph = pn.generate3DGraph(terrainSize);


    for (int x = 0; x < terrainSize; x++) {
        for (int y = 0; y < terrainSize; y++) {

            //TODO: round the z value to int
            double nf = terrainGraph[x][y];
            int z = (int)std::round(nf * 500) - 300;

            Vector3 pos = {x*CUBE_SIZE, z*CUBE_SIZE, y*CUBE_SIZE};

            Cube cube = Cube();
            cube.position = pos;
            cube.color = { (unsigned char)GetRandomValue(0, 255), (unsigned char)(int)std::round(100*nf), (unsigned char)(int)std::round(255*nf), 255 };
            
            cubes.push_back(cube);
        }
    }


    // Store the camera's previous position and rotation
    Vector3 prevCameraPos = camera.position;
    Vector3 prevCameraTarget = camera.target;

    int visibleCubes = 0 ;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        visibleCubes = 0 ;
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
                // ##################################


                // Draw the cubes that are visible to the camera
                for (Cube& cube : cubes) {
                    if (cube.isCubeVisible(camera)) {
                        //fade-in effect
                        if(cube.color.a + 10  < 255){
                            cube.color.a += 10;
                            // if(cube.color.a >= 255) cube.color.a = 255;
                        } else {
                            cube.color.a = 255;
                        }
                        
                        visibleCubes += 1;
                        DrawCube(cube.position, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, cube.color);

                    } 
                }

            // End drawing
            EndMode3D();

            DrawText(TextFormat("visible Cubes: %d", visibleCubes), 10, 30, 20, BLACK);
            DrawText(TextFormat("Seed: %d", seed), 10, 50, 20, BLACK);
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
