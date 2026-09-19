#include "raylib.h"
#include "kitchen.h"
#include "../globalFunctions.h"

// types
typedef enum {
    // cake shape layers
    CIRCLE,
    SQUARE,
    STAR,
    // toppings layers
    COCONUT_TOPPING,
    STRAWBERRY_TOPPING,
    SPRINKLES_TOPPING,
    // none
    NO_LAYER,
} LayerType;

// textures
static Texture2D background;
static Texture2D counter;
static Texture2D containersBottomLayer;
static Texture2D containersTopLayer;
static Texture2D signs;
static Texture2D ovenOff;
static Texture2D ovenOn;
static Texture2D cart;
// struct textures for items in kitchen
static Texture2D batterSheet;
static Texture2D icingSheet;
static Texture2D circlePanSheet;
static Texture2D squarePanSheet;
static Texture2D starPanSheet;

static Texture2D circleCakeSheet;
static Texture2D squareCakeSheet;
static Texture2D starCakeSheet;

static Texture2D circleIcingSheet;
static Texture2D squareIcingSheet;
static Texture2D starIcingSheet;

// variables
bool circleInOven = false; // shape of pan placed in oven
bool squareInOven = false;
bool starInOven = false;

bool circleOutOven = false; // shape of cake that has been baked
bool squareOutOven = false;
bool starOutOven = false;

bool icingOnCake = false; // detects whether or not player dragged and dropped icing over existing cake layer
int icingFlavorIndex = 0;

bool cakeReset = false;

int cakeLayer = 1; // keeps track of how many layers of cake have been added

LayerType cakeLayer1Type = NO_LAYER;
LayerType cakeLayer2Type = NO_LAYER;
LayerType cakeLayer3Type = NO_LAYER;

LayerType icingLayer1Type = NO_LAYER;
LayerType icingLayer2Type = NO_LAYER;
LayerType icingLayer3Type = NO_LAYER;

// structs
        // pos,       defPos,      w&h,  spriteIndex, frame, frameReset, isPressed
Item batter[3] = {
    { { 528, 590 }, { 528, 590 }, { 135, 103 }, { 0, 0 }, 0, 0, false }, // vanilla
    { { 621, 590 }, { 621, 590 }, { 135, 103 }, { 0, 1 }, 0, 0, false }, // chocolate
    { { 720, 590 }, { 720, 590 }, { 135, 103 }, { 0, 2 }, 0, 0, false } // strawberry
};
        // pos,       defPos,      w&h,  spriteIndex, frame, frameReset, isPressed
Item icing[3] = {
    { { 888, 556 }, { 888, 556 }, { 88, 170 }, { 0, 0 }, 0, 0, false }, // vanilla
    { { 987, 556 }, { 987, 556 }, { 88, 170 }, { 0, 1 }, 0, 0, false }, // chocolate
    { { 1086, 556 }, { 1086, 556 }, { 88, 170 }, { 0, 2 }, 0, 0, false } // strawberry
};
        // pos,        defPos,       w&h,    spriteIndex, frame, frameReset, isPressed
Item pan[3] = {
    { { 600, 870 }, { 600, 870 }, { 233, 122 }, { 0, 0 }, 0, 0, false },  // circle
    { { 925, 880 }, { 925, 880 }, { 250, 105 }, { 0, 0 }, 0, 0, false },  // square
    { { 1250, 890 }, { 1250, 890 }, { 196, 110 }, { 0, 0 }, 0, 0, false } // star
};

Item cakeLayers[3] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Item icingLayers[3] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Rectangle ovenHitbox = { 1650, 920, 345, 200 }; // hitbox for oven
Rectangle cakeHitbox = { 1650, 450, 345, 300 }; // hitbox for placing icing over the cake
Rectangle cartHitbox = {2229, 620, 260, 214}; // hitbox for placing cake on cart

void initKitchen(void){
    background = LoadTexture("assets/kitchen/kitchenBg.png");
    counter = LoadTexture("assets/kitchen/counter.png");
    containersBottomLayer = LoadTexture("assets/kitchen/containers1.png");
    containersTopLayer = LoadTexture("assets/kitchen/containers2.png");
    signs = LoadTexture("assets/kitchen/signs.png");

    ovenOff = LoadTexture("assets/kitchen/ovenOff.png");
    ovenOn = LoadTexture("assets/kitchen/ovenOn.png");

    cart = LoadTexture("assets/kitchen/cart.png");

    // struct textures for items in kitchen
    batterSheet = LoadTexture("assets/kitchen/items/batter.png");
    icingSheet = LoadTexture("assets/kitchen/items/icingSheet.png");

    circlePanSheet = LoadTexture("assets/kitchen/items/circlePanSheet.png");
    squarePanSheet = LoadTexture("assets/kitchen/items/squarePanSheet.png");
    starPanSheet = LoadTexture("assets/kitchen/items/starPanSheet.png");
    
    circleCakeSheet = LoadTexture("assets/kitchen/items/circleCakeSheet.png");
    squareCakeSheet = LoadTexture("assets/kitchen/items/squareCakeSheet.png");
    starCakeSheet = LoadTexture("assets/kitchen/items/starCakeSheet.png");

    circleIcingSheet = LoadTexture("assets/kitchen/items/circleIcingSheet.png");
    squareIcingSheet = LoadTexture("assets/kitchen/items/squareIcingSheet.png");
    starIcingSheet = LoadTexture("assets/kitchen/items/starIcingSheet.png");
}

void unloadKitchen(void){
    UnloadTexture(background);
    UnloadTexture(counter);
    UnloadTexture(containersBottomLayer);
    UnloadTexture(containersTopLayer);
    UnloadTexture(signs);

    UnloadTexture(ovenOff);
    UnloadTexture(ovenOn);

    UnloadTexture(cart);
    // struct textures for items in kitchen
    UnloadTexture(batterSheet);
    UnloadTexture(icingSheet);
    UnloadTexture(circlePanSheet);
    UnloadTexture(squarePanSheet);
    UnloadTexture(starPanSheet);
    
    UnloadTexture(circleCakeSheet);
    UnloadTexture(squareCakeSheet);
    UnloadTexture(starCakeSheet);

    UnloadTexture(circleIcingSheet);
    UnloadTexture(squareIcingSheet);
    UnloadTexture(starIcingSheet);
}

void cakeStack(bool *shapeOutOven, bool *shapeInOven, LayerType *cakeLayerType, int cakeLayerTypeNumber, float y, float offsetY, int panIndex, int cakeLayerIndex){
    if (*shapeOutOven == true){
        *cakeLayerType = cakeLayerTypeNumber;
        *shapeInOven = false;
        cakeLayer++;

        cakeLayers[cakeLayerIndex] = (Item){ { 1697, y - offsetY }, { 1697, y - offsetY }, { 243, 105 }, { 0, (pan[panIndex].spriteIndex.y - 1) }, 0, 0, false };
        *shapeOutOven = false;
    }
}

void icingStack(LayerType *icingLayerType, LayerType *cakeLayerType, int icingLayerIndex, float y, float offsetY, int icingFlavorIndex){
    if (cakeLayer >= 2 && icingOnCake == true){
        *icingLayerType = *cakeLayerType;
        icingLayers[icingLayerIndex] = (Item){ { 1697, y - (offsetY * cakeLayer - 1) }, { 1697, y - (offsetY * cakeLayer - 1) }, { 243, 105 }, { 0, icingFlavorIndex }, 0, 0, false };
        icingOnCake = false;
    } else {
        icingOnCake = false;
    }
}

void cakeLogic(Vector2 mouse){
    switch(cakeLayer){
        case 1:
            // bool *shapeOutOven, CakeLayerType *cakeLayerType, int cakeLayerTypeNumber, float y, float offsetY, int panIndex, int cakeLayerIndex
            cakeStack(&circleOutOven, &circleInOven, &cakeLayer1Type, 0, 655, 0, 0, 0);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer1Type, 1, 655, 0, 1, 0);
            cakeStack(&starOutOven, &starInOven, &cakeLayer1Type, 2, 655, 0, 2, 0);
            break;
        case 2:
            icingStack(&icingLayer1Type, &cakeLayer1Type, 0, cakeLayers[0].position.y, 0, icingFlavorIndex);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer2Type, 0, cakeLayers[0].position.y, 55, 0, 1);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer2Type, 1, cakeLayers[0].position.y, 55, 1, 1);
            cakeStack(&starOutOven, &starInOven, &cakeLayer2Type, 2, cakeLayers[0].position.y, 55, 2, 1);
            break;
        case 3:
            icingStack(&icingLayer2Type, &cakeLayer2Type, 1, cakeLayers[1].position.y, 0, icingFlavorIndex);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer3Type, 0, cakeLayers[1].position.y, 55, 0, 2);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer3Type, 1, cakeLayers[1].position.y, 55, 1, 2);
            cakeStack(&starOutOven, &starInOven, &cakeLayer3Type, 2, cakeLayers[1].position.y, 55, 2, 2);
            break;
        case 4:
            icingStack(&icingLayer3Type, &cakeLayer3Type, 2, cakeLayers[2].position.y, 0, icingFlavorIndex);
    }
}

void cakeRender(void){
    if (cakeLayer1Type != NO_LAYER) {

        if (cakeLayer1Type == CIRCLE){
            renderItem(&cakeLayers[0], circleCakeSheet);
        } 
        else if (cakeLayer1Type == SQUARE){
            renderItem(&cakeLayers[0], squareCakeSheet);
        } 
        else if (cakeLayer1Type == STAR){
            renderItem(&cakeLayers[0], starCakeSheet);
        }
    }
    if (icingLayer1Type != NO_LAYER){
        if (icingLayer1Type == CIRCLE){
            renderItem(&icingLayers[0], circleIcingSheet);
        }
        else if (icingLayer1Type == SQUARE){
            renderItem(&icingLayers[0], squareIcingSheet);
        } 
        else if (icingLayer1Type == STAR){
            renderItem(&icingLayers[0], starIcingSheet);
        }
    }
    
    if (cakeLayer2Type != NO_LAYER) {

        if (cakeLayer2Type == CIRCLE){
            renderItem(&cakeLayers[1], circleCakeSheet);
        } 
        else if (cakeLayer2Type == SQUARE){
            renderItem(&cakeLayers[1], squareCakeSheet);
        } 
        else if (cakeLayer2Type == STAR){
            renderItem(&cakeLayers[1], starCakeSheet);
        }
    }
    if (icingLayer2Type != NO_LAYER){
        if (icingLayer2Type == CIRCLE){
            renderItem(&icingLayers[1], circleIcingSheet);
        }
        else if (icingLayer2Type == SQUARE){
            renderItem(&icingLayers[1], squareIcingSheet);
        } 
        else if (icingLayer2Type == STAR){
            renderItem(&icingLayers[1], starIcingSheet);
        }
    }

    if (cakeLayer3Type != NO_LAYER) {

        if (cakeLayer3Type == CIRCLE){
            renderItem(&cakeLayers[2], circleCakeSheet);
        } 
        else if (cakeLayer3Type == SQUARE){
            renderItem(&cakeLayers[2], squareCakeSheet);
        } 
        else if (cakeLayer3Type == STAR){
            renderItem(&cakeLayers[2], starCakeSheet);
        }
    }
    if (icingLayer3Type != NO_LAYER){
        if (icingLayer3Type == CIRCLE){
            renderItem(&icingLayers[2], circleIcingSheet);
        }
        else if (icingLayer3Type == SQUARE){
            renderItem(&icingLayers[2], squareIcingSheet);
        } 
        else if (icingLayer3Type == STAR){
            renderItem(&icingLayers[2], starIcingSheet);
        }
    }
}

void kitchenLogic(GameState *currentState, Vector2 mouse){
    // cake batter items
    // Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse
    
    // drop item logic located under cake making steps
    if (circleInOven == false && squareInOven == false && starInOven == false){
        for (int i = 0; i < 3; i++){ dragItemOffset(&batter[i], 93, (batter[i].dimensions.y / 2), 45, 0, 86, 103, mouse); }
    }
    // dropping logic for when adding batter to the pans
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

    // icing items
    if (circleInOven == false && squareInOven == false && starInOven == false){
        for (int i = 0; i < 3; i++){ dragItem(&icing[i], mouse); }
    }
    for (int i = 0; i < 3; i++){
        if (cakeLayer > 1){
                dropItemReturnBoolInt(&icing[i], mouse, cakeHitbox, &icingOnCake, true, &icingFlavorIndex, i);
        } else {
            dropItemReturn(&icing[i], mouse);
        }
    }

    // pan items
    for (int i = 0; i < 3; i++){ 
        if (circleInOven == false && squareInOven == false && starInOven == false){ dragItem(&pan[i], mouse); }
        if (pan[i].spriteIndex.y > 0 && i == 0 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &circleInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 1 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &squareInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 2 && cakeLayer < 4){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &starInOven, true);

        } else {
            dropItemReturn(&pan[i], mouse);
        }
    }

    cakeLogic(mouse);

    // logic for carrying all of the cakes
    if (circleInOven == false && squareInOven == false && starInOven == false){
        dragItemOffset(&cakeLayers[0], 121, 50, 0, -105, 243, 210, mouse);
        dropItemReturnBool(&cakeLayers[0], mouse, cartHitbox, &cakeReset, true);
    }
    if (cakeLayers[0].isPressed == true){
        icingLayers[0].position.x = cakeLayers[0].position.x;
        icingLayers[0].position.y = cakeLayers[0].position.y; 
 
        cakeLayers[1].position.x = cakeLayers[0].position.x;
        cakeLayers[1].position.y = cakeLayers[0].position.y - 55;

        icingLayers[1].position.x = cakeLayers[1].position.x;
        icingLayers[1].position.y = cakeLayers[1].position.y;

        cakeLayers[2].position.x = cakeLayers[1].position.x;
        cakeLayers[2].position.y = cakeLayers[1].position.y - 55;

        icingLayers[2].position.x = cakeLayers[2].position.x;
        icingLayers[2].position.y = cakeLayers[2].position.y;

    } else if (cakeLayers[0].isPressed == false){ // sends back to default positions after releasing left click
        icingLayers[0].position.x = cakeLayers[0].defaultPosition.x;
        icingLayers[0].position.y = cakeLayers[0].defaultPosition.y;

        cakeLayers[1].position.x = cakeLayers[1].defaultPosition.x;
        cakeLayers[1].position.y = cakeLayers[1].defaultPosition.y;

        icingLayers[1].position.x = cakeLayers[1].defaultPosition.x;
        icingLayers[1].position.y = cakeLayers[1].defaultPosition.y;

        cakeLayers[2].position.x = cakeLayers[2].defaultPosition.x;
        cakeLayers[2].position.y = cakeLayers[2].defaultPosition.y;

        icingLayers[2].position.x = cakeLayers[2].defaultPosition.x;
        icingLayers[2].position.y = cakeLayers[2].defaultPosition.y;
    }

    // logic for dropping the cakes onto the cart and resetting the cake layers
    if (cakeReset == true){
        for (int i = 0; i < 3; i++){ cakeLayers[i] = (Item){ {0}, {0}, {0}, { 0, 0 }, 0, 0, false }; }
        cakeLayer = 1;
        cakeLayer1Type = NO_LAYER;
        icingLayer1Type = NO_LAYER;
        cakeLayer2Type = NO_LAYER;
        icingLayer2Type = NO_LAYER;
        cakeLayer3Type = NO_LAYER;
        icingLayer3Type = NO_LAYER;
        cakeReset = false;
    }

} // end kitchenLogic

void kitchenRender(void){
    ClearBackground(PINK);
    // background elements bottom layer
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(counter, 492, 700, WHITE);
    DrawTexture(containersBottomLayer, 570, 600, WHITE);
    DrawTexture(signs, 582, 409, WHITE);

    DrawTexture(ovenOff, 1570, 700, WHITE);
    DrawText(TextFormat("icing flavor: %i", icingFlavorIndex), 20, 20, 50, MAROON);
    DrawText(TextFormat("icing bool: %i", icingOnCake), 20, 70, 50, MAROON);
    // oven on animation
    if (circleInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &circleOutOven, true); }
    if (squareInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &squareOutOven, true); }
    if (starInOven == true){ DrawTextureTimedBool(1.0f, ovenOn, (Vector2){ 1570, 700 }, &starOutOven, true); }

    DrawTexture(cart, 2025, 675, WHITE);

    // DrawRectangle(ovenHitbox.x, ovenHitbox.y, ovenHitbox.width, ovenHitbox.height, RED); // hitbox for oven

    // struct textures for items in kitchen bottom layer

    if (batter[2].isPressed == false){ renderItem(&batter[2], batterSheet); }
    if (batter[1].isPressed == false){ renderItem(&batter[1], batterSheet); }
    if (batter[0].isPressed == false){ renderItem(&batter[0], batterSheet); }

    if (icing[2].isPressed == false){ renderItem(&icing[2], icingSheet); }
    if (icing[1].isPressed == false){ renderItem(&icing[1], icingSheet); }
    if (icing[0].isPressed == false){ renderItem(&icing[0], icingSheet); }

    if (pan[2].isPressed == false){ renderItem(&pan[2], starPanSheet); }
    if (pan[1].isPressed == false){ renderItem(&pan[1], squarePanSheet); }
    if (pan[0].isPressed == false){ renderItem(&pan[0], circlePanSheet); }

    // background elements top layer
    DrawTexture(containersTopLayer, 570, 600, WHITE);

    // struct textures for items in kitchen top layer
        // cake layers
    cakeRender();

    if (batter[2].isPressed == true){ renderItem(&batter[2], batterSheet); }
    if (batter[1].isPressed == true){ renderItem(&batter[1], batterSheet); }
    if (batter[0].isPressed == true){ renderItem(&batter[0], batterSheet); }

    if (icing[2].isPressed == true){ renderItem(&icing[2], icingSheet); }
    if (icing[1].isPressed == true){ renderItem(&icing[1], icingSheet); }
    if (icing[0].isPressed == true){ renderItem(&icing[0], icingSheet); }

    if (pan[2].isPressed == true){ renderItem(&pan[2], starPanSheet); }
    if (pan[1].isPressed == true){ renderItem(&pan[1], squarePanSheet); }
    if (pan[0].isPressed == true){ renderItem(&pan[0], circlePanSheet); }

    // debugging
    // DrawRectangle(cakeHitbox.x, cakeHitbox.y, cakeHitbox.width, cakeHitbox.height, WHITE);
} // end kitchenRender