#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    // Create an array
    float windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // Initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // Gravity
    const int gravity {1'000}; // (pixels/s)/s

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Anim data for nebula
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowDimensions[0], windowDimensions[1] - nebula.height/8},  // Vector2 pos
        0, // int frame
        1.0/12.0,  // float update Time
        0.0 // float running Time
        
    };

    // Anim data for nebula 2
    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8},
        0, // in frame 
        1.0/16.0, // float update time
        0.0 // float running time
 
    };

    // Nebula animation variables
    int nebVel {-200};


    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0; 
    scarfyData.runningTime = 0.0;
    scarfyData.updateTime = 1.0/12.0;
   
    //jump velocity
    const int jumpVel{-600}; // (Pixels/s)/s    
    // Set Velocity
    int velocity {0}; //pixels/frame
    // is the rectangle in the air?
    bool isInAir {};

    
     //Target Frames per second
    SetTargetFPS(60);


    // While loop - Game logic starts
    while(!WindowShouldClose()) 
    {

        // Delta time
        float dt{GetFrameTime()};

             
    
        // Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);
    
        // Ground check
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

        // update nebula position
        nebData.pos.x += nebVel * dt;
        // update nebula2 position
        neb2Data.pos.x += nebVel * dt; 
        // update scarfy position
        scarfyData.pos.y += velocity * dt;

        // Update Runnning Time - This works as a timer, everytime running time reaches 12th of a second, 
        // we update the frame but also restart the time. 
        // Scarfy
       if(!isInAir)
       { 
        scarfyData.runningTime += dt;
        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0.0;
            // Update Scarfy Animation Rec
            scarfyData.rec.x = scarfyData.frame*scarfyData.rec.width;
            scarfyData.frame++; 
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
        }
       }
       // Nebula running Time - For animation
       nebData.runningTime += dt;
       if (nebData.runningTime >= nebData.updateTime)
       {
            nebData.runningTime = 0.0;
            // Update Nebula Animation Rec
            nebData.rec.x = nebData.frame*nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
       }
       // Nebula 2 animation fram
       neb2Data.runningTime += dt;
       if (neb2Data.runningTime >= neb2Data.updateTime)
       {
            neb2Data.runningTime = 0.0;
            // Update Nebula 2 Animation Rec
            neb2Data.rec.x = neb2Data.frame*neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
       }
      
        
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        // Draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // Draw the second nebula
        DrawTextureRec (nebula, neb2Data.rec, neb2Data.pos, BLUE);

        // Stop Drawing
        EndDrawing();
        
        
        }
   
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}
