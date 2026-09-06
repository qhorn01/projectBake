#include "raylib.h"
#include "raymath.h"
#include "gameStates/testCenter.h"
#include "gameStates/kitchen.h"
#include "globalFunctions.h"

#define MAX(a, b) ((a)>(b)? (a) : (b)) // taken from letterbox Raylib example
#define MIN(a, b) ((a)<(b)? (a) : (b))

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Global Variables Definition (local to this module)

// Module Functions Declaration

//----------------------------------------------------------------------------------
// Program main entry pointglobalFunctions.c
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    const int screenWidth = 150;
    const int screenHeight = 150;

    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib");
    SetWindowMinSize(384, 216);

    int gameScreenWidth = 2560;
    int gameScreenHeight = 1440;

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

    // instantiations for data types ex. enums and structs
    GameState currentState = KITCHEN;

    int previousState = -1; // used to check if the gamestate has changed, if it has then it will unload the previous gamestate's textures and load the new one

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight); // Compute required framebuffer scaling

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = { 0 };
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale;
        virtualMouse = Vector2Clamp(virtualMouse, (Vector2){ 0, 0 }, (Vector2){ (float)gameScreenWidth, (float)gameScreenHeight });
        
        // switches through gamestate textures
        if (currentState != previousState){
            switch(previousState){
                case MENU:
                    break;
                case KITCHEN:
                    unloadKitchen();
                    break;
                case TEST_CENTER:
                    break;
                default:
                    break;
            }
            switch(currentState){
                case MENU:
                    break;
                case KITCHEN:
                    initKitchen();
                    break;
                case TEST_CENTER:
                    break;
                default:
                    break;
            }
            previousState = currentState;
        }
        
        // switches through gamestate logic
        switch(currentState){
            case MENU:
                break;
            case KITCHEN:
                kitchenLogic(&currentState, virtualMouse);
                break;
            case TEST_CENTER:
                testCenterLogic(&currentState, virtualMouse);
                break;
            default:
                break;
        }
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        // switches through gamestate rendering
        switch(currentState){
            case MENU:
                break;
            case KITCHEN:
                kitchenRender();
                break;
            case TEST_CENTER:
                testCenterRender();
                break;
            default:
                break;
        }

        EndTextureMode();

        // Draw
        BeginDrawing();
            ClearBackground(BLACK); // Clear screen background

            DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                (Rectangle){ (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);    // Unload render texture
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}