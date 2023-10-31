#include "raylib.h"

int main()
{

    // Constant dimensions
    const int WindowWidth {512};
    const int WindowHeight {380};

    // Initialize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher!");

    // Gravity
    const int gravity {1'000}; // (pixels/s)/s

    // Texture function - Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = WindowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = WindowHeight - scarfyRec.height;
    
    // Set Velocity
    int velocity {0}; //pixels/frame

    // is the rectangle in the air?
    bool isInAir {};

    //jump velocity
    const int jumpVel{-600}; // (Pixels/s)/s

     //Target Frames per second
    SetTargetFPS(60);


    // While loop
    while(!WindowShouldClose()) 
    {

    // Delta time
    float dt{GetFrameTime()};
   
    // Begin Drawing
    BeginDrawing();
    ClearBackground(WHITE);


   
    // Ground check
    if (scarfyPos.y >= WindowHeight - scarfyRec.height)
    {
    // Rectangle is on the ground
    velocity = 0;
    isInAir = false;
    }
    else
    {
    // Rectangle is in the air - Add gravity
    velocity += gravity * dt;
    isInAir = true;
    }

    
    // Button Actions - Jump
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
        velocity += jumpVel;
    }

    // update Y position
    scarfyPos.y += velocity * dt;

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop Drawing
    EndDrawing();
    
    
    }
    UnloadTexture(scarfy);
    CloseWindow();

}
