#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "globalFunctions.h"
#include "types.h"
#include "gameStates.h"

void testCenterLogic(GameState *currentState, Item *testItem, Vector2 mouse){
    dragItem(testItem, mouse);
}
void testCenterRender(Item *testItem){
    ClearBackground(GetColor(0xAAAAAA));

    DrawRectangle(testItem->position.x, testItem->position.y, 
        testItem->dimensions.x, testItem->dimensions.y, BLACK);

}