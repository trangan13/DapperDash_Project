#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
}


int main()
{

    // Constant dimensions
    const int WindowWidth {512};
    const int WindowHeight {380};

    // Initialize window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher!");

    // Gravity
    const int gravity {1'000}; // (pixels/s)/s

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Anim data for nebula
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {WindowWidth, WindowHeight - nebula.height/8},  // Vector2 pos
        0, // int frame
        1.0/12.0,  // float update Time
        0.0 // float running Time
        
    };

    // Anim data for nebula 2
    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {WindowWidth + 300, WindowHeight - nebula.height/8},
        0, // in frame 
        1.0/16.0, // float update time
        0.0 // float running time
 
    };

    /* Not needed again as we are using strucs now. 
    Rectangle nebRec {0.0, 0.0, nebula.width/8, nebula.height/8};
    // For Rectangle elementars are {x(float), y(float), widht, height}
     This is no longer needed, I we initialized Rectangle earlier. 
    nebulaRec.width = nebula.width/8; //the size of the actual rectangloe
    nebulaRec.height = nebula.height/8;
    nebulaRec.x = 0.0; // where in the sprite we get the image from
    nebulaRec.y = 0.0;
    
   
    Vector2 nebPos {WindowWidth, WindowHeight - nebRec.height};
    // Again not needed as we initialized directly. 
    // nebulaPos.x = WindowWidth;
    //nebulaPos.y = WindowHeight - nebulaRec.height;
    // nebula 2
   Rectangle neb2Rec {0.0, 0.0, nebula.width/8, nebula.height/8};
   Vector2 neb2Pos {WindowWidth + 300, WindowHeight - nebRec.height};

    int neb2Frame {0};
    const float neb2UpdateTime {1.0/16.0};
    float neb2RunningTime {};
    // we are using the same velocity    
    // Nebula x velocity (pixels/second)
    int nebVel{-200}; //
    // nebula frame animation 
    int nebFrame {0};
    // nebula update time
    const float nebUpdateTime {1.0/12.0};
    float nebRunningTime {};
    */
    



    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData ScarfyData;
    ScarfyData.rec.width = scarfy.width/6;
    ScarfyData.rec.height = scarfy.height;
    ScarfyData.rec.x = 0;
    ScarfyData.rec.y = 0;
    ScarfyData.pos.x = WindowWidth/2 - ScarfyData.rec.width/2;
    ScarfyData.pos.y = WindowHeight - ScarfyData.rec.height;
    ScarfyData.frame = 0; 
    ScarfyData.runningTime = 0.0;
    ScarfyData.updateTime = 1.0/12.0;
    
    /* No longer needed because we created a struct with all the data
    this is to be able to repeat the element again without copying information. 

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = WindowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = WindowHeight - scarfyRec.height;
    // Scarfy frame animation
    int frame {0};
    // Scarfy Amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime {};
    //jump velocity
    const int jumpVel{-600}; // (Pixels/s)/s    
    // Set Velocity
    int velocity {0}; //pixels/frame
    // is the rectangle in the air?
    bool isInAir {};
    */
    

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

        // update nebula position
        nebPos.x += nebVel * dt;
        // update nebula2 position
        neb2Pos.x += nebVel * dt; 
        // update scarfy position
        scarfyPos.y += velocity * dt;

        // Update Runnning Time - This works as a timer, everytime running time reaches 12th of a second, 
        // we update the frame but also restart the time. 
        // Scarfy
       if(!isInAir)
       { 
        runningTime += dt;
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            // Update Scarfy Animation Rec
            scarfyRec.x = frame*scarfyRec.width;
            frame++; 
            if (frame > 5)
            {
                frame = 0;
            }
        }
       }
       // Nebula running Time - For animation
       nebRunningTime += dt;
       if (nebRunningTime >= nebUpdateTime)
       {
            nebRunningTime = 0.0;
            // Update Nebula Animation Rec
            nebRec.x = nebFrame*nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
       }
       // Nebula 2 animation fram
       neb2RunningTime += dt;
       if (neb2RunningTime >= neb2UpdateTime)
       {
            neb2RunningTime = 0.0;
            // Update Nebula 2 Animation Rec
            neb2Rec.x = neb2Frame*neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
       }
      
        
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        // Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // Draw the second nebula
        DrawTextureRec (nebula, neb2Rec, neb2Pos, BLUE);

        // Stop Drawing
        EndDrawing();
        
        
        }
   
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}
