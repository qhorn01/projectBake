#include "raylib.h"
#include "kitchen.h"
#include "../globalFunctions.h"

// types
typedef enum {
    // cake layers
    CIRCLE_CAKE,
    SQUARE_CAKE,
    TRIANGLE_CAKE,
    // icing layers
    CIRCLE_ICING,
    SQUARE_ICING,
    TRIANGLE_ICING,
    // toppings layers
    COCONUT_TOPPING,
    STRAWBERRY_TOPPING,
    SPRINKLES_TOPPING,
    // none
    NO_LAYER,
} CakeLayerType;

typedef enum {
    NO_FLAVOR = 0,
    VANILLA = 1,
    CHOCOLATE = 2,
    STRAWBERRY = 3,
} Flavor;

// textures
static Texture2D background;
static Texture2D counter;
static Texture2D containersBottomLayer;
static Texture2D containersTopLayer;
static Texture2D signs;
static Texture2D ovenOff;
static Texture2D ovenOn;
// struct textures for items in kitchen
static Texture2D batterSheet;
static Texture2D circlePanSheet;
static Texture2D squarePanSheet;
static Texture2D trianglePanSheet;

static Texture2D circleCakeSheet;
static Texture2D squareCakeSheet;
static Texture2D triangleCakeSheet;

// variables
bool circleInOven = false; // shape of pan placed in oven
bool squareInOven = false;
bool triangleInOven = false;

bool circleOutOven = false; // shape of cake that has been baked
bool squareOutOven = false;
bool triangleOutOven = false;

int cakeLayer = 1; // keeps track of how many layers of cake have been added

CakeLayerType cakeLayer1Type = NO_LAYER;
CakeLayerType cakeLayer2Type = NO_LAYER;
CakeLayerType cakeLayer3Type = NO_LAYER;

// structs
        // pos,       defPos,      w&h,  spriteIndex, frame, frameReset, isPressed
Item batter[3] = {
    { { 528, 590 }, { 528, 590 }, { 135, 103 }, { 0, 0 }, 0, 0, false }, // vanilla
    { { 621, 590 }, { 621, 590 }, { 135, 103 }, { 0, 1 }, 0, 0, false }, // chocolate
    { { 720, 590 }, { 720, 590 }, { 135, 103 }, { 0, 2 }, 0, 0, false } // strawberry
}; 
        // pos,        defPos,       w&h,    spriteIndex, frame, frameReset, isPressed
Item pan[3] = {
    { { 600, 870 }, { 600, 870 }, { 233, 122 }, { 0, 0 }, 0, 0, false },  // circle
    { { 925, 880 }, { 925, 880 }, { 250, 105 }, { 0, 0 }, 0, 0, false },  // square
    { { 1250, 890 }, { 1250, 890 }, { 182, 109 }, { 0, 0 }, 0, 0, false } // triangle
};

Item cakeLayers[3] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Rectangle ovenHitbox = { 1650, 920, 345, 200 }; // hitbox for oven

void initKitchen(void){
    background = LoadTexture("assets/kitchen/kitchenBg.png");
    counter = LoadTexture("assets/kitchen/counter.png");
    containersBottomLayer = LoadTexture("assets/kitchen/containers1.png");
    containersTopLayer = LoadTexture("assets/kitchen/containers2.png");
    signs = LoadTexture("assets/kitchen/signs.png");

    ovenOff = LoadTexture("assets/kitchen/ovenOff.png");
    ovenOn = LoadTexture("assets/kitchen/ovenOn.png");

    // struct textures for items in kitchen
    batterSheet = LoadTexture("assets/kitchen/items/batter.png");

    circlePanSheet = LoadTexture("assets/kitchen/items/circlePanSheet.png");
    squarePanSheet = LoadTexture("assets/kitchen/items/squarePanSheet.png");
    trianglePanSheet = LoadTexture("assets/kitchen/items/trianglePanSheet.png");
    
    circleCakeSheet = LoadTexture("assets/kitchen/items/circleCakeSheet.png");
    squareCakeSheet = LoadTexture("assets/kitchen/items/squareCakeSheet.png");
    triangleCakeSheet = LoadTexture("assets/kitchen/items/triangleCakeSheet.png");
}

void unloadKitchen(void){
    UnloadTexture(background);
    UnloadTexture(counter);
    UnloadTexture(containersBottomLayer);
    UnloadTexture(containersTopLayer);
    UnloadTexture(signs);

    UnloadTexture(ovenOff);
    UnloadTexture(ovenOn);
    // struct textures for items in kitchen
    UnloadTexture(batterSheet);
    UnloadTexture(circlePanSheet);
    UnloadTexture(squarePanSheet);
    UnloadTexture(trianglePanSheet);
    
    UnloadTexture(circleCakeSheet);
    UnloadTexture(squareCakeSheet);
    UnloadTexture(triangleCakeSheet);
}

void cakeStack(bool *shapeOutOven, bool *shapeInOven, CakeLayerType *cakeLayerType, int cakeLayerTypeNumber, float y, float offsetY, int panIndex, int cakeLayerIndex){
    if (*shapeOutOven == true){
        *cakeLayerType = cakeLayerTypeNumber;
        *shapeInOven = false;
        cakeLayer++;

        cakeLayers[cakeLayerIndex] = (Item){ { 1697, y - offsetY }, { 1697, y - offsetY }, { 243, 105 }, { 0, (pan[panIndex].spriteIndex.y - 1) }, 0, 0, false };
        *shapeOutOven = false;
    }
}

void cakeLogic(Vector2 mouse){
    switch(cakeLayer){
        case 1:
            // bool *shapeOutOven, CakeLayerType *cakeLayerType, int cakeLayerTypeNumber, float y, float offsetY, int panIndex, int cakeLayerIndex
            cakeStack(&circleOutOven, &circleInOven, &cakeLayer1Type, 0, 655, 0, 0, 0);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer1Type, 1, 655, 0, 1, 0);
            cakeStack(&triangleOutOven, &triangleInOven, &cakeLayer1Type, 2, 655, 0, 2, 0);
            break;
        case 2:
            cakeStack(&circleOutOven, &circleInOven, &cakeLayer2Type, 0, cakeLayers[0].position.y, 55, 0, 1);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer2Type, 1, cakeLayers[0].position.y, 55, 1, 1);
            cakeStack(&triangleOutOven, &triangleInOven, &cakeLayer2Type, 2, cakeLayers[0].position.y, 55, 2, 1);
            break;
        case 3:
            cakeStack(&circleOutOven, &circleInOven, &cakeLayer3Type, 0, cakeLayers[1].position.y, 55, 0, 2);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer3Type, 1, cakeLayers[1].position.y, 55, 1, 2);
            cakeStack(&triangleOutOven, &triangleInOven, &cakeLayer3Type, 2, cakeLayers[1].position.y, 55, 2, 2);
            break;
    }
}

void cakeRender(void){
    if (cakeLayer1Type != NO_LAYER) {

        if (cakeLayer1Type == CIRCLE_CAKE){
            renderItem(&cakeLayers[0], circleCakeSheet);
        } 
        else if (cakeLayer1Type == SQUARE_CAKE){
            renderItem(&cakeLayers[0], squareCakeSheet);
        } 
        else if (cakeLayer1Type == TRIANGLE_CAKE){
            renderItem(&cakeLayers[0], triangleCakeSheet);
        }
    }
    
    if (cakeLayer2Type != NO_LAYER) {

        if (cakeLayer2Type == CIRCLE_CAKE){
            renderItem(&cakeLayers[1], circleCakeSheet);
        } 
        else if (cakeLayer2Type == SQUARE_CAKE){
            renderItem(&cakeLayers[1], squareCakeSheet);
        } 
        else if (cakeLayer2Type == TRIANGLE_CAKE){
            renderItem(&cakeLayers[1], triangleCakeSheet);
        }
    }

    if (cakeLayer3Type != NO_LAYER) {

        if (cakeLayer3Type == CIRCLE_CAKE){
            renderItem(&cakeLayers[2], circleCakeSheet);
        } 
        else if (cakeLayer3Type == SQUARE_CAKE){
            renderItem(&cakeLayers[2], squareCakeSheet);
        } 
        else if (cakeLayer3Type == TRIANGLE_CAKE){
            renderItem(&cakeLayers[2], triangleCakeSheet);
        }
    }
}

void kitchenLogic(GameState *currentState, Vector2 mouse){
    // cake batter items
    // Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse
    
    // drop item logic located under cake making steps
    if (circleInOven == false && squareInOven == false && triangleInOven == false){
        for (int i = 0; i < 3; i++){ dragItemOffset(&batter[i], 93, (batter[i].dimensions.y / 2), 45, 0, 86, 103, mouse); }
    }
    // pan items
    for (int i = 0; i < 3; i++){ 
        if (circleInOven == false && squareInOven == false && triangleInOven == false){ dragItem(&pan[i], mouse); }
        if (pan[i].spriteIndex.y > 0 && i == 0 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &circleInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 1 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &squareInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 2 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &triangleInOven, true);

        } else {
            dropItemReturn(&pan[i], mouse);
        }
    }

    // cake making steps
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
           if(CheckCollisionPointRec(mouse, 
                                    (Rectangle)
                                    {pan[i].position.x, 
                                    pan[i].position.y, 
                                    pan[i].dimensions.x, 
                                    pan[i].dimensions.y}) 
                                    && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
                                    && batter[j].isPressed == true){

                pan[i].spriteIndex.y = batter[j].spriteIndex.y + 1;
                if (i == 0){ pan[1].spriteIndex.y = 0; pan[2].spriteIndex.y = 0; }
                if (i == 1){ pan[0].spriteIndex.y = 0; pan[2].spriteIndex.y = 0; }
                if (i == 2){ pan[0].spriteIndex.y = 0; pan[1].spriteIndex.y = 0; }
            }
        }
    }
    for (int i = 0; i < 3; i++){ dropItemReturn(&batter[i], mouse); }

    cakeLogic(mouse);

} // end kitchenLogic

void kitchenRender(void){
    ClearBackground(PINK);
    // background elements bottom layer
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(counter, 492, 700, WHITE);
    DrawTexture(containersBottomLayer, 570, 600, WHITE);
    DrawTexture(signs, 582, 409, WHITE);

    DrawTexture(ovenOff, 1570, 700, WHITE);
    
    DrawText(TextFormat("cake layer: %i", cakeLayer), 20, 20, 20, MAROON);

    // oven on animation
    if (circleInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &circleOutOven, true); }
    if (squareInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &squareOutOven, true); }
    if (triangleInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &triangleOutOven, true); }

    // DrawRectangle(ovenHitbox.x, ovenHitbox.y, ovenHitbox.width, ovenHitbox.height, RED); // hitbox for oven

    // struct textures for items in kitchen bottom layer

    if (batter[2].isPressed == false){ renderItem(&batter[2], batterSheet); }
    if (batter[1].isPressed == false){ renderItem(&batter[1], batterSheet); }
    if (batter[0].isPressed == false){ renderItem(&batter[0], batterSheet); }

    if (pan[2].isPressed == false){ renderItem(&pan[2], trianglePanSheet); }
    if (pan[1].isPressed == false){ renderItem(&pan[1], squarePanSheet); }
    if (pan[0].isPressed == false){ renderItem(&pan[0], circlePanSheet); }

        // cake layers
    cakeRender();    

    // background elements top layer
    DrawTexture(containersTopLayer, 570, 600, WHITE);

    // struct textures for items in kitchen top layer
    if (batter[2].isPressed == true){ renderItem(&batter[2], batterSheet); }
    if (batter[1].isPressed == true){ renderItem(&batter[1], batterSheet); }
    if (batter[0].isPressed == true){ renderItem(&batter[0], batterSheet); }

    if (pan[2].isPressed == true){ renderItem(&pan[2], trianglePanSheet); }
    if (pan[1].isPressed == true){ renderItem(&pan[1], squarePanSheet); }
    if (pan[0].isPressed == true){ renderItem(&pan[0], circlePanSheet); }
} // end kitchenRender