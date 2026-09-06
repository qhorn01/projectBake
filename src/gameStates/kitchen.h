#ifndef KITCHEN_H
#define KITCHEN_H

#include "raylib.h"
#include "../globalFunctions.h"

void initKitchen(void);
void unloadKitchen(void);

void kitchenLogic(GameState *currentState, Vector2 mouse);
void kitchenRender(void);

#endif