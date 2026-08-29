#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"

typedef enum { // defined in main.c
    MENU,
    KITCHEN,
    TEST_CENTER // for debugging and testing only
} GameState; // changes different gamestates ex. main menu, rooms, levels, minigames, etc.

void testCenterLogic(GameState *currentState);
void testCenterRender();

#endif