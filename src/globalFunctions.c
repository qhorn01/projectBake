#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "globalFunctions.h"
#include "types.h"

void dragItem(Item *item, Vector2 mouse){
    if(CheckCollisionPointRec(mouse, (Rectangle){ item->position.x, item->position.y, 
        item->dimensions.x, item->dimensions.y }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            item->isPressed = true;
    }
    if(item->isPressed == true){
        
        item->position = mouse;
        
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            item->position = item->defaultPosition;
            item->isPressed = false;
        }
    }
}