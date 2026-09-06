#include "raylib.h"
#include "kitchen.h"
#include "../globalFunctions.h"

// textures
static Texture2D background;
static Texture2D counter;
static Texture2D containersBottomLayer;
static Texture2D containersTopLayer;
static Texture2D signs;
static Texture2D ovenOff;
static Texture2D ovenOn;
// struct textures for items in kitchen
static Texture2D batterSheet;
static Texture2D circlePanSheet;

// structs
        // pos,       defPos,      w&h,  spriteIndex, frame, frameReset, isPressed
Item batter[3] = {
    { { 528, 590 }, { 528, 590 }, { 135, 103 }, { 0, 0 }, 0, 0, false }, // vanilla
    { { 621, 590 }, { 621, 590 }, { 135, 103 }, { 0, 1 }, 0, 0, false }, // chocolate
    { { 720, 590 }, { 720, 590 }, { 135, 103 }, { 0, 2 }, 0, 0, false } // strawberry
}; 
                    // pos,        defPos,      w&h,   spriteIndex, frame, frameReset, isPressed
Item circlePan = { { 600, 870 }, { 600, 870 }, { 233, 122 }, { 0, 0 }, 0, 0, false };

void initKitchen(void){
    background = LoadTexture("assets/kitchen/kitchenBg.png");
    counter = LoadTexture("assets/kitchen/counter.png");
    containersBottomLayer = LoadTexture("assets/kitchen/containers1.png");
    containersTopLayer = LoadTexture("assets/kitchen/containers2.png");
    signs = LoadTexture("assets/kitchen/signs.png");

    ovenOff = LoadTexture("assets/kitchen/ovenOff.png");
    ovenOn = LoadTexture("assets/kitchen/ovenOn.png");

    // struct textures for items in kitchen
    batterSheet = LoadTexture("assets/kitchen/items/batter.png");

    circlePanSheet = LoadTexture("assets/kitchen/items/circlePans.png");
}

void unloadKitchen(void){
    UnloadTexture(background);
    UnloadTexture(counter);
    UnloadTexture(containersBottomLayer);
    UnloadTexture(containersTopLayer);
    UnloadTexture(signs);

    UnloadTexture(ovenOff);
    UnloadTexture(ovenOn);
    // struct textures for items in kitchen
    UnloadTexture(batterSheet);

    UnloadTexture(circlePanSheet);
}

void renderBatter(Item *item){
    DrawTextureRec(batterSheet, 
                    (Rectangle){ 
                        item->spriteIndex.x, 
                        item->spriteIndex.y * item->dimensions.y,
                        item->dimensions.x, 
                        item->dimensions.y },
                        (Vector2){ item->position.x, item->position.y }, 
                        WHITE);
}

void kitchenLogic(GameState *currentState, Vector2 mouse){
    // cake batter items
    // Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse
    dragItemOffset(&batter[0], 93, (batter[0].dimensions.y / 2), 45, 0, 86, 103, mouse);
    dragItemOffset(&batter[1], 93, (batter[1].dimensions.y / 2), 45, 0, 86, 103, mouse);
    dragItemOffset(&batter[2], 93, (batter[2].dimensions.y / 2), 45, 0, 86, 103, mouse);
    // pan items
    dragItem(&circlePan, mouse);
    dropItemReturn(&circlePan, mouse);
    // cake making steps
    for (int i = 0; i < 3; i++){
        if(CheckCollisionPointRec(mouse, 
                                (Rectangle)
                                {circlePan.position.x, 
                                circlePan.position.y, 
                                circlePan.dimensions.x, 
                                circlePan.dimensions.y}) 
                                && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
                                && batter[i].isPressed == true){
            circlePan.spriteIndex.y = batter[i].spriteIndex.y + 1;
            batter[i].position = batter[i].defaultPosition;
            batter[i].isPressed = false;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            batter[i].position = batter[i].defaultPosition;
            batter[i].isPressed = false;
        }
    }
}

void kitchenRender(void){
    ClearBackground(PINK);
    // background elements bottom layer
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(counter, 492, 700, WHITE);
    DrawTexture(containersBottomLayer, 570, 600, WHITE);
    DrawTexture(signs, 582, 409, WHITE);

    DrawTexture(ovenOff, 1570, 700, WHITE);

    // struct textures for items in kitchen bottom layer

    if (batter[2].isPressed == false){ renderBatter(&batter[2]); }
    if (batter[1].isPressed == false){ renderBatter(&batter[1]); }
    if (batter[0].isPressed == false){ renderBatter(&batter[0]); }

    // background elements top layer
    DrawTexture(containersTopLayer, 570, 600, WHITE);

    // struct textures for items in kitchen top layer

    DrawTextureRec(circlePanSheet,
                    (Rectangle){ 
                        circlePan.spriteIndex.x, 
                        circlePan.spriteIndex.y * circlePan.dimensions.y,
                        circlePan.dimensions.x, 
                        circlePan.dimensions.y },
                        (Vector2){ circlePan.position.x, circlePan.position.y }, WHITE);

    
    if (batter[2].isPressed == true){ renderBatter(&batter[2]); }
    if (batter[1].isPressed == true){ renderBatter(&batter[1]); }
    if (batter[0].isPressed == true){ renderBatter(&batter[0]); }
    
}