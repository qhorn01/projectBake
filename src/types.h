#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include "raylib.h"

typedef struct {
    Vector2 position; // x and y position of item
    Vector2 defaultPosition; // x and y position of item after left mouse button is released
    Vector2 dimensions; // width and height of item
    Vector2 spriteIndex; // x, y index on sprite sheet
    float frame; // counts the number of frames counted
    float frameReset; // determines how many frames have to pass before it resets
    bool isPressed;
} Item; // item that can be dragged across the screen with the mouse and dropped at a specific location on the screen

#endif