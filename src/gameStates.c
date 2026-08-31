#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "globalFunctions.h"
#include "types.h"
#include "gameStates.h"

// Test center functions and variables with logic/render functions placed at the bottom of the list
static Rectangle tlDrop = { 0, 0, 120, 120}; // top left
static Rectangle trDrop = { 1800, 0, 120, 120}; // top right
static Rectangle blDrop = {0, 960, 120, 120}; // bottom left
static Rectangle brDrop = {1800, 960, 120, 120}; // bottom right
                    // pos, defPos, w&h, spriteIndex, frame, frameReset, isPressed
Item testItem = { { 0, 0 }, { 0, 0 }, { 120, 120 }, { 0, 0 }, 0, 30, false };

void testCenterLogic(GameState *currentState, Vector2 mouse){
    // Item *item, Vector2 mouse, Rectangle rectangle
    snapItem(&testItem, mouse, tlDrop);
    // Item *item, Vector2 mouse, Rectangle rectangle
    snapItem(&testItem, mouse, trDrop);
    // Item *item, Vector2 mouse, Rectangle rectangle
    snapItem(&testItem, mouse, blDrop);
    // Item *item, Vector2 mouse, Rectangle rectangle
    snapItem(&testItem, mouse, brDrop);


    // Item *item, Vector2 mouse
    dragItem(&testItem, mouse);

}
void testCenterRender(){
    ClearBackground(GetColor(0xAAAAAA));

    DrawRectangle(tlDrop.x, tlDrop.y, tlDrop.width, tlDrop.height, RED);
    DrawRectangle(trDrop.x, trDrop.y, trDrop.width, trDrop.height, RED);
    DrawRectangle(blDrop.x, blDrop.y, blDrop.width, blDrop.height, RED);
    DrawRectangle(brDrop.x, brDrop.y, brDrop.width, brDrop.height, RED);

    DrawRectangle(testItem.position.x, testItem.position.y, 
                    testItem.dimensions.x, testItem.dimensions.y, BLACK);

}