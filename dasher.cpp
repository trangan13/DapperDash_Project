#include "raylib.h"

int main()
{

    // Constant dimensions
    const int WindowWidth {512};
    const int WindowHeight {380};

    // Initialize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher!");

    // Gravity
    const int gravity {1}; // (pixels/frame)/frame

    // rectangle dimensions
    const int width {50};
    const int height {80};
    
    // Set Velocity
    int posY {WindowHeight - height};
    int velocity {0}; //pixels/frame

    // is the rectangle in the air?
    bool isInAir {posY != WindowHeight - height};

    //jump velocity
    const int jumpVel{-22};

     //Target Frames per second
    SetTargetFPS(60);


    // While loop
    while(!WindowShouldClose()) 
    {
   
    // Begin Drawing
    BeginDrawing();
    ClearBackground(WHITE);

   
    // Ground check
    if (posY >= WindowHeight - height)
    {
    // Rectangle is on the ground
    velocity = 0;
    isInAir = false;
    }
    else
    {
    // Rectangle is in the air
    velocity += gravity;
    isInAir = true;
    }

    
    // Button Actions
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
        velocity += jumpVel;
    }
    

    // update Y position
    posY += velocity;

    DrawRectangle (WindowWidth/2, posY, width, height, BLUE);

    // Stop Drawing
    EndDrawing();
    
    
    }
    CloseWindow();

}
