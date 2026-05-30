#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "ball.h"

int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(240);
    
    // CAMERA
    Camera camera = {0};
    camera.position = (Vector3){ 5.0f, 2.5f, 5.0f };    
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                               
    camera.projection = CAMERA_PERSPECTIVE;     
    
    // Billboard
    Texture2D bill = LoadTexture("res/ptak.png");             

    Rectangle source = { 0.0f, 0.0f, (float)bill.width, (float)bill.height };
    Vector2 size = { source.width/source.height, 1.0f };
    Vector2 origin = Vector2Scale(size, 0.5f);
    Vector3 billPos = { 0.0f, origin.y, 0.0f };    


    Texture2D roadTexture = LoadTexture("res/road.png");
    Mesh mesh = GenMeshPlane(10.0f, 10.0f, 1, 1);
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = roadTexture;

    float rotation = 0.0f;

    while (!WindowShouldClose()) 
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        rotation += 0.4f;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModel(model, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

                DrawBillboard(camera, bill, billPos, 1.0f, WHITE);
                DrawBillboard(camera, bill, billPos + (Vector3){ 1.0f, 0.0f, 1.0f }, 1.0f, WHITE);

                

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(bill); 
    UnloadTexture(roadTexture);    
    UnloadModel(model);

    CloseWindow();  

    return 0;
}