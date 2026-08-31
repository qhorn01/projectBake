#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "globalFunctions.h"
#include "types.h"
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
        
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            item->position = item->defaultPosition;
            item->isPressed = false;
        }
    }
}

void snapItem(Item *item, Vector2 mouse, Rectangle rectangle){ // allows players to place item in a specific place
    if(CheckCollisionPointRec(mouse, rectangle) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            item->defaultPosition.x = rectangle.x;
            item->defaultPosition.y = rectangle.y;
    }
}
