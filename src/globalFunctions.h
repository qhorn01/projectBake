#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"

typedef enum { // defined in main.c
    MENU,
    KITCHEN,
    TEST_CENTER // for debugging and testing only
} GameState; // changes different testCenter ex. main menu, rooms, levels, minigames, etc.

typedef struct {
    Vector2 position; // x and y position of item
    Vector2 defaultPosition; // x and y position of item after left mouse button is released
    Vector2 dimensions; // width and height of item
    Vector2 spriteIndex; // x, y index on sprite sheet
    float frame; // counts the number of frames counted
    float frameReset; // determines how many frames have to pass before it resets
    bool isPressed;
} Item; // item that can be dragged across the screen with the mouse and dropped at a specific location on the screen

// Item struct:

// allows played to drag item accross screen while left mouse button is held down
void dragItem(Item *item, Vector2 mouse);
// same as dragItem but allows for offset and hitbox values to be specified
void dragItemOffset(Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse);
// returns item to default position when left mouse button is released
void dropItemReturn(Item *item, Vector2 mouse);
// changes a bool value when an item is dropped in a specific place
void dropItemReturnBool(Item *item, Vector2 mouse, Rectangle rectangle, bool *boolVar, bool trueOrFalse);
// allows players to place item in a specific place
void dropItemSnap(Item *item, Vector2 mouse, Rectangle rectangle);
// renders item to screen
void renderItem(Item *item, Texture2D spriteSheet);

#endif