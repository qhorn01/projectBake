#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "globalFunctions.h"
/*
This .c file contains functions that correspond with specific structs
Everytime you see something like "Item struct:" that indicates that all
functions below it are to only be used for that specified struct
*/

// Item struct:
void dragItem(Item *item, Vector2 mouse){ // allows played to drag item accross screen while left mouse button is held down
    if(CheckCollisionPointRec(mouse, (Rectangle){ item->position.x, item->position.y, 
        item->dimensions.x, item->dimensions.y }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            item->isPressed = true;
    }
    if(item->isPressed == true){
        
        item->position.x = mouse.x - (item->dimensions.x / 2);
        item->position.y = mouse.y - (item->dimensions.y / 2);
        
    }
}

void dragItemOffset(Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse){ // same as dragItem but allows for offset and hitbox values to be specified
    if(CheckCollisionPointRec(mouse, (Rectangle){ (item->position.x + hitboxX), (item->position.y + hitboxY), 
        hitboxW, hitboxH }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            item->isPressed = true;
    }
    if(item->isPressed == true){
        
        item->position.x = mouse.x - (offsetX);
        item->position.y = mouse.y - (offsetY);
        

    }
}

void dropItemReturn(Item *item, Vector2 mouse){ // returns item to default position when left mouse button is released
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        item->position = item->defaultPosition;
        item->isPressed = false;
    }
}

void dropItemReturnBool(Item *item, Vector2 mouse, Rectangle rectangle, bool *boolVar, bool trueOrFalse){ // changes a bool value when an item is dropped in a specific place
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && item->isPressed == true){
        if(CheckCollisionPointRec(mouse, rectangle)){
            *boolVar = trueOrFalse;
        } else {
            *boolVar = !trueOrFalse;
        }
        item->position = item->defaultPosition;
        item->isPressed = false;
    }
}

void dropItemSnap(Item *item, Vector2 mouse, Rectangle rectangle){ // allows players to place item in a specific place
    if(CheckCollisionPointRec(mouse, rectangle) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            item->defaultPosition.x = rectangle.x;
            item->defaultPosition.y = rectangle.y;
            item->isPressed = false;
    }
}

void renderItem(Item *item, Texture2D spriteSheet){ // renders item to screen
    DrawTextureRec(spriteSheet, 
                    (Rectangle){ 
                        item->spriteIndex.x * item->dimensions.x, 
                        item->spriteIndex.y * item->dimensions.y,
                        item->dimensions.x, 
                        item->dimensions.y },
                        (Vector2){ item->position.x, item->position.y }, 
                        WHITE);
}

// Texture2D struct: (Raylib struct)

void DrawTextureTimed(float duration, Texture2D texture, Vector2 position){ // draws a texture for a specific amount of time
    static bool isDrawing = true;
    static float frame = 0;
    if (isDrawing) {
        DrawTexture(texture, position.x, position.y, WHITE);
        frame += GetFrameTime(); 
    }
    if (frame >= duration) {
        isDrawing = false; frame = 0; 
    }
}

void DrawTextureTimedBool(float duration, Texture2D texture, Vector2 position, bool *boolVar, bool trueOrFalse){ // draws a texture for a specific amount of time and changes a bool value
    static float frame = 0;
    
    DrawTexture(texture, position.x, position.y, WHITE);
    frame += GetFrameTime(); 
    
    if (frame >= duration) {
        *boolVar = trueOrFalse;
        frame = 0;
    }
}