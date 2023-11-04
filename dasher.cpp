#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
// update running time
data.runningTime += deltaTime;
if (data.runningTime >= data.updateTime)
{
    data.runningTime = 0.0;
    // update animation fram
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrame)
    {
        data.frame = 0;
    }
}
return data;

}

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

   
   const int sizeOfNebulae{6};
    // Array of 
    AnimData nebulae[sizeOfNebulae]{};
 
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }


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

    // background image
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    
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

        // Movemente for the background, conditional to bring it back again. 
        bgX -= 20 * dt;
        if (bgX <= -background.width*2)
        {
            bgX = 0;
        }
        //draw background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0}; 
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        
        // Ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Update the position of each nebula
            nebulae[i].pos.x += nebVel * dt;
        }
        

        // update scarfy position
        scarfyData.pos.y += velocity * dt;

        // Update Runnning Time - This works as a timer, everytime running time reaches 12th of a second, 
        // we update the frame but also restart the time. 
        // Scarfy
       if(!isInAir)
       { 
            scarfyData = updateAnimData (scarfyData, dt, 5);
       }

            
 
        for (int i = 0; i < sizeOfNebulae; i++)
        {
           nebulae[i] = updateAnimData (nebulae[i], dt, 7); 
           
            // Draw each nebulae
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        // Stop Drawing
        EndDrawing();
        
        
        }
   
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();

}
