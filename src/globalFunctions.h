#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"
#include "types.h"
#include "globalFunctions.h"

void dragItem(Item *item, Vector2 mouse);
void snapItem(Item *item, Vector2 mouse, Rectangle rectangle);

#endif