#include "raylib.h"
#include "kitchen.h"
#include "../globalFunctions.h"

// types
typedef enum {
    // cake/icing shape layers
    CIRCLE,
    SQUARE,
    STAR,
    // toppings layers
    STRAWBERRY_TOPPING,
    COCONUT_TOPPING,
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

static Texture2D toppingsSheet;

// variables
bool circleInOven = false; // shape of pan placed in oven
bool squareInOven = false;
bool starInOven = false;

bool circleOutOven = false; // shape of cake that has been baked
bool squareOutOven = false;
bool starOutOven = false;

bool icingOnCake = false; // detects whether or not player dragged and dropped icing over existing cake layer
int icingFlavorIndex = 0; // tracks the specific icing flavor to add to the cake

bool toppingOnCake = false; // detects whether player has dragged and dropped topping over existing cake/icing layer
int toppingFlavorIndex = 0; // tracks the specific topping to add to the cake

bool cakeReset = false;

int cakeLayer = 1; // keeps track of how many layers of cake have been added

LayerType cakeLayer1Type = NO_LAYER;
LayerType cakeLayer2Type = NO_LAYER;
LayerType cakeLayer3Type = NO_LAYER;
LayerType cakeLayer4Type = NO_LAYER;
LayerType cakeLayer5Type = NO_LAYER;
LayerType cakeLayer6Type = NO_LAYER;

LayerType icingLayer1Type = NO_LAYER;
LayerType icingLayer2Type = NO_LAYER;
LayerType icingLayer3Type = NO_LAYER;
LayerType icingLayer4Type = NO_LAYER;
LayerType icingLayer5Type = NO_LAYER;
LayerType icingLayer6Type = NO_LAYER;

LayerType toppingsLayer1Type = NO_LAYER;
LayerType toppingsLayer2Type = NO_LAYER;
LayerType toppingsLayer3Type = NO_LAYER;
LayerType toppingsLayer4Type = NO_LAYER;
LayerType toppingsLayer5Type = NO_LAYER;
LayerType toppingsLayer6Type = NO_LAYER;


LayerType toppingsType = NO_LAYER;
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
        // pos,        defPos,       w&h,    spriteIndex, frame, frameReset, isPressed
Item topping[3] = {
    { { 1167, 672 }, { 1167, 672 }, { 243, 105 }, { 0, 0 }, 0, 0, false }, // strawberry
    { { 1262, 672 }, { 1262, 672 }, { 243, 105 }, { 0, 1 }, 0, 0, false }, // coconut
    { { 1355, 672 }, { 1355, 672 }, { 243, 105 }, { 0, 2 }, 0, 0, false } // sprinkles
};

Item cakeLayers[6] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Item icingLayers[6] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Item toppingsLayer[6] = {
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false },
    { {0}, {0}, {0}, { 0, 0 }, 0, 0, false }
};

Rectangle ovenHitbox = { 1650, 920, 345, 200 }; // hitbox for oven
Rectangle cakeHitbox = { 1650, 450, 345, 300 }; // hitbox for placing icing over the cake
Rectangle cartHitbox = { 2229, 620, 260, 214 }; // hitbox for placing cake on cart

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

    toppingsSheet = LoadTexture("assets/kitchen/items/toppingsSheet.png");
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

    UnloadTexture(toppingsSheet);
}

void cakeStack(bool *shapeOutOven, bool *shapeInOven, LayerType *cakeLayerType, int cakeLayerTypeNumber, float y, float offsetY, int panIndex, int cakeLayerIndex){
    if (*shapeOutOven == true){
        *cakeLayerType = cakeLayerTypeNumber;
        *shapeInOven = false;
        cakeLayer++;

        toppingsLayer1Type = NO_LAYER;
        toppingsLayer2Type = NO_LAYER;
        toppingsLayer3Type = NO_LAYER;
        toppingsLayer4Type = NO_LAYER;
        toppingsLayer5Type = NO_LAYER;
        toppingsLayer6Type = NO_LAYER;

        cakeLayers[cakeLayerIndex] = (Item){ { 1697, y - offsetY }, { 1697, y - offsetY }, { 243, 105 }, { 0, (pan[panIndex].spriteIndex.y - 1) }, 0, 0, false };
        *shapeOutOven = false;
    }
}

void icingStack(LayerType *icingLayerType, LayerType *cakeLayerType, int icingLayerIndex, float y, float offsetY, int icingFlavorIndex){
    if (cakeLayer >= 2 && icingOnCake == true){
        *icingLayerType = *cakeLayerType;
        icingLayers[icingLayerIndex] = (Item){ { 1697, y - (offsetY * cakeLayer - 1) }, { 1697, y - (offsetY * cakeLayer - 1) }, { 243, 105 }, { 0, icingFlavorIndex }, 0, 0, false };

        toppingsLayer1Type = NO_LAYER;
        toppingsLayer2Type = NO_LAYER;
        toppingsLayer3Type = NO_LAYER;
        toppingsLayer4Type = NO_LAYER;
        toppingsLayer5Type = NO_LAYER;
        toppingsLayer6Type = NO_LAYER;
        
        icingOnCake = false;
    } else {
        icingOnCake = false;
    }
}

void toppingsStack(LayerType *toppingsType, int toppingFlavorIndex, int toppingsLayerIndex, float y, float offsetY){
    if (cakeLayer >= 2 && toppingOnCake == true){
        *toppingsType = toppingFlavorIndex + 3; // + 3 offsets it to topping types rather than shape types
        toppingsLayer[toppingsLayerIndex] = (Item){ { 1697, y - (offsetY * cakeLayer - 1) }, { 1697, y - (offsetY * cakeLayer - 1) }, { 243, 105 }, { 0, toppingFlavorIndex }, 0, 0, false };
        toppingOnCake = false;
    } else{
        toppingOnCake = false;
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
            toppingsStack(&toppingsLayer1Type, toppingFlavorIndex, 0, cakeLayers[0].position.y, 0);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer2Type, 0, cakeLayers[0].position.y, 55, 0, 1);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer2Type, 1, cakeLayers[0].position.y, 55, 1, 1);
            cakeStack(&starOutOven, &starInOven, &cakeLayer2Type, 2, cakeLayers[0].position.y, 55, 2, 1);
            break;
        case 3:
            icingStack(&icingLayer2Type, &cakeLayer2Type, 1, cakeLayers[1].position.y, 0, icingFlavorIndex);
            toppingsStack(&toppingsLayer2Type, toppingFlavorIndex, 1, cakeLayers[1].position.y, 0);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer3Type, 0, cakeLayers[1].position.y, 55, 0, 2);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer3Type, 1, cakeLayers[1].position.y, 55, 1, 2);
            cakeStack(&starOutOven, &starInOven, &cakeLayer3Type, 2, cakeLayers[1].position.y, 55, 2, 2);
            break;
        case 4:
            icingStack(&icingLayer3Type, &cakeLayer3Type, 2, cakeLayers[2].position.y, 0, icingFlavorIndex);
            toppingsStack(&toppingsLayer3Type, toppingFlavorIndex, 2, cakeLayers[2].position.y, 0);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer4Type, 0, cakeLayers[2].position.y, 55, 0, 3);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer4Type, 1, cakeLayers[2].position.y, 55, 1, 3);
            cakeStack(&starOutOven, &starInOven, &cakeLayer4Type, 2, cakeLayers[2].position.y, 55, 2, 3);
            break;
        case 5:
            icingStack(&icingLayer4Type, &cakeLayer4Type, 3, cakeLayers[3].position.y, 0, icingFlavorIndex);
            toppingsStack(&toppingsLayer4Type, toppingFlavorIndex, 3, cakeLayers[3].position.y, 0);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer5Type, 0, cakeLayers[3].position.y, 55, 0, 4);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer5Type, 1, cakeLayers[3].position.y, 55, 1, 4);
            cakeStack(&starOutOven, &starInOven, &cakeLayer5Type, 2, cakeLayers[3].position.y, 55, 2, 4);
            break;
        case 6:
            icingStack(&icingLayer5Type, &cakeLayer5Type, 4, cakeLayers[4].position.y, 0, icingFlavorIndex);
            toppingsStack(&toppingsLayer5Type, toppingFlavorIndex, 4, cakeLayers[4].position.y, 0);

            cakeStack(&circleOutOven, &circleInOven, &cakeLayer6Type, 0, cakeLayers[4].position.y, 55, 0, 5);
            cakeStack(&squareOutOven, &squareInOven, &cakeLayer6Type, 1, cakeLayers[4].position.y, 55, 1, 5);
            cakeStack(&starOutOven, &starInOven, &cakeLayer6Type, 2, cakeLayers[4].position.y, 55, 2, 5);
            break;
        case 7:
            icingStack(&icingLayer6Type, &cakeLayer6Type, 5, cakeLayers[4].position.y, 0, icingFlavorIndex);
            toppingsStack(&toppingsLayer6Type, toppingFlavorIndex, 5, cakeLayers[4].position.y, 0);
            break;
        default:
            break;
    }
}

void cakeRender(void){
    // layer 1
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
    if (toppingsLayer1Type != NO_LAYER){
        renderItem(&toppingsLayer[0], toppingsSheet);
    }
    // layer 2
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
    if (toppingsLayer2Type != NO_LAYER){
        renderItem(&toppingsLayer[1], toppingsSheet);
    }
    // layer 3
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
    if (toppingsLayer3Type != NO_LAYER){
        renderItem(&toppingsLayer[2], toppingsSheet);
    }
    // layer 4
    if (cakeLayer4Type != NO_LAYER) {

        if (cakeLayer4Type == CIRCLE){
            renderItem(&cakeLayers[3], circleCakeSheet);
        } 
        else if (cakeLayer4Type == SQUARE){
            renderItem(&cakeLayers[3], squareCakeSheet);
        } 
        else if (cakeLayer4Type == STAR){
            renderItem(&cakeLayers[3], starCakeSheet);
        }
    }
    if (icingLayer4Type != NO_LAYER){
        if (icingLayer4Type == CIRCLE){
            renderItem(&icingLayers[3], circleIcingSheet);
        }
        else if (icingLayer4Type == SQUARE){
            renderItem(&icingLayers[3], squareIcingSheet);
        } 
        else if (icingLayer4Type == STAR){
            renderItem(&icingLayers[3], starIcingSheet);
        }
    }
    if (toppingsLayer4Type != NO_LAYER){
        renderItem(&toppingsLayer[3], toppingsSheet);
    }
    // layer 5
    if (cakeLayer5Type != NO_LAYER) {

        if (cakeLayer5Type == CIRCLE){
            renderItem(&cakeLayers[4], circleCakeSheet);
        } 
        else if (cakeLayer5Type == SQUARE){
            renderItem(&cakeLayers[4], squareCakeSheet);
        } 
        else if (cakeLayer5Type == STAR){
            renderItem(&cakeLayers[4], starCakeSheet);
        }
    }
    if (icingLayer5Type != NO_LAYER){
        if (icingLayer5Type == CIRCLE){
            renderItem(&icingLayers[4], circleIcingSheet);
        }
        else if (icingLayer5Type == SQUARE){
            renderItem(&icingLayers[4], squareIcingSheet);
        } 
        else if (icingLayer5Type == STAR){
            renderItem(&icingLayers[4], starIcingSheet);
        }
    }
    if (toppingsLayer5Type != NO_LAYER){
        renderItem(&toppingsLayer[4], toppingsSheet);
    }
    // layer 6
    if (cakeLayer6Type != NO_LAYER) {

        if (cakeLayer6Type == CIRCLE){
            renderItem(&cakeLayers[5], circleCakeSheet);
        } 
        else if (cakeLayer6Type == SQUARE){
            renderItem(&cakeLayers[5], squareCakeSheet);
        } 
        else if (cakeLayer6Type == STAR){
            renderItem(&cakeLayers[5], starCakeSheet);
        }
    }
    if (icingLayer6Type != NO_LAYER){
        if (icingLayer6Type == CIRCLE){
            renderItem(&icingLayers[5], circleIcingSheet);
        }
        else if (icingLayer6Type == SQUARE){
            renderItem(&icingLayers[5], squareIcingSheet);
        } 
        else if (icingLayer6Type == STAR){
            renderItem(&icingLayers[5], starIcingSheet);
        }
    }
    if (toppingsLayer6Type != NO_LAYER){
        renderItem(&toppingsLayer[5], toppingsSheet);
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
    // topping items
    if (circleInOven == false && squareInOven == false && starInOven == false){
                                    // Item *item, float offsetX, float offsetY, float hitboxX, float hitboxY, float hitboxW, float hitboxH, Vector2 mouse
        for (int i = 0; i < 3; i++){ dragItemOffset(&topping[i], 120, 20, 45, 0, 84, 50, mouse); }
    }
    for (int i = 0; i < 3; i++){
        if (cakeLayer > 1){
                dropItemReturnBoolInt(&topping[i], mouse, cakeHitbox, &toppingOnCake, true, &toppingFlavorIndex, i);
        } else {
            dropItemReturn(&topping[i], mouse);
        }
    }

    // pan items
    for (int i = 0; i < 3; i++){ 
        if (circleInOven == false && squareInOven == false && starInOven == false){ dragItem(&pan[i], mouse); }
        if (pan[i].spriteIndex.y > 0 && i == 0 && cakeLayer < 7){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &circleInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 1 && cakeLayer < 7){
            dropItemReturnBool(&pan[i], mouse, ovenHitbox, &squareInOven, true);

        } else if (pan[i].spriteIndex.y > 0 && i == 2 && cakeLayer < 7){
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
    if (cakeLayers[0].isPressed == true){ // moves the other cake layers and icing layers with the first cake layer
        icingLayers[0].position.x = cakeLayers[0].position.x;
        icingLayers[0].position.y = cakeLayers[0].position.y;
 
        toppingsLayer[0].position.x = cakeLayers[0].position.x;
        toppingsLayer[0].position.y = cakeLayers[0].position.y;

        cakeLayers[1].position.x = cakeLayers[0].position.x;
        cakeLayers[1].position.y = cakeLayers[0].position.y - 55;

        icingLayers[1].position.x = cakeLayers[1].position.x;
        icingLayers[1].position.y = cakeLayers[1].position.y;

        toppingsLayer[1].position.x = cakeLayers[1].position.x;
        toppingsLayer[1].position.y = cakeLayers[1].position.y;

        cakeLayers[2].position.x = cakeLayers[1].position.x;
        cakeLayers[2].position.y = cakeLayers[1].position.y - 55;

        icingLayers[2].position.x = cakeLayers[2].position.x;
        icingLayers[2].position.y = cakeLayers[2].position.y;

        toppingsLayer[2].position.x = cakeLayers[2].position.x;
        toppingsLayer[2].position.y = cakeLayers[2].position.y;

        cakeLayers[3].position.x = cakeLayers[2].position.x;
        cakeLayers[3].position.y = cakeLayers[2].position.y - 55;

        icingLayers[3].position.x = cakeLayers[3].position.x;
        icingLayers[3].position.y = cakeLayers[3].position.y;

        toppingsLayer[3].position.x = cakeLayers[3].position.x;
        toppingsLayer[3].position.y = cakeLayers[3].position.y;

        cakeLayers[4].position.x = cakeLayers[3].position.x;
        cakeLayers[4].position.y = cakeLayers[3].position.y - 55;

        icingLayers[4].position.x = cakeLayers[4].position.x;
        icingLayers[4].position.y = cakeLayers[4].position.y;

        toppingsLayer[4].position.x = cakeLayers[4].position.x;
        toppingsLayer[4].position.y = cakeLayers[4].position.y;

        cakeLayers[5].position.x = cakeLayers[4].position.x;
        cakeLayers[5].position.y = cakeLayers[4].position.y - 55;

        icingLayers[5].position.x = cakeLayers[5].position.x;
        icingLayers[5].position.y = cakeLayers[5].position.y;

        toppingsLayer[5].position.x = cakeLayers[5].position.x;
        toppingsLayer[5].position.y = cakeLayers[5].position.y;

    } else if (cakeLayers[0].isPressed == false){ // sends back to default positions after releasing left click
        icingLayers[0].position.x = cakeLayers[0].defaultPosition.x;
        icingLayers[0].position.y = cakeLayers[0].defaultPosition.y;

        toppingsLayer[0].position.x = cakeLayers[0].defaultPosition.x;
        toppingsLayer[0].position.y = cakeLayers[0].defaultPosition.y;

        cakeLayers[1].position.x = cakeLayers[1].defaultPosition.x;
        cakeLayers[1].position.y = cakeLayers[1].defaultPosition.y;

        icingLayers[1].position.x = cakeLayers[1].defaultPosition.x;
        icingLayers[1].position.y = cakeLayers[1].defaultPosition.y;

        toppingsLayer[1].position.x = cakeLayers[1].defaultPosition.x;
        toppingsLayer[1].position.y = cakeLayers[1].defaultPosition.y;

        cakeLayers[2].position.x = cakeLayers[2].defaultPosition.x;
        cakeLayers[2].position.y = cakeLayers[2].defaultPosition.y;

        icingLayers[2].position.x = cakeLayers[2].defaultPosition.x;
        icingLayers[2].position.y = cakeLayers[2].defaultPosition.y;

        toppingsLayer[2].position.x = cakeLayers[2].defaultPosition.x;
        toppingsLayer[2].position.y = cakeLayers[2].defaultPosition.y;

        cakeLayers[3].position.x = cakeLayers[3].defaultPosition.x;
        cakeLayers[3].position.y = cakeLayers[3].defaultPosition.y;

        icingLayers[3].position.x = cakeLayers[3].defaultPosition.x;
        icingLayers[3].position.y = cakeLayers[3].defaultPosition.y;

        toppingsLayer[3].position.x = cakeLayers[3].defaultPosition.x;
        toppingsLayer[3].position.y = cakeLayers[3].defaultPosition.y;

        cakeLayers[4].position.x = cakeLayers[4].defaultPosition.x;
        cakeLayers[4].position.y = cakeLayers[4].defaultPosition.y;

        icingLayers[4].position.x = cakeLayers[4].defaultPosition.x;
        icingLayers[4].position.y = cakeLayers[4].defaultPosition.y;

        toppingsLayer[4].position.x = cakeLayers[4].defaultPosition.x;
        toppingsLayer[4].position.y = cakeLayers[4].defaultPosition.y;

        cakeLayers[5].position.x = cakeLayers[5].defaultPosition.x;
        cakeLayers[5].position.y = cakeLayers[5].defaultPosition.y;

        icingLayers[5].position.x = cakeLayers[5].defaultPosition.x;
        icingLayers[5].position.y = cakeLayers[5].defaultPosition.y;

        toppingsLayer[5].position.x = cakeLayers[5].defaultPosition.x;
        toppingsLayer[5].position.y = cakeLayers[5].defaultPosition.y;
    }

    // logic for dropping the cakes onto the cart and resetting the cake layers
    if (cakeReset == true){
        for (int i = 0; i < 6; i++){ cakeLayers[i] = (Item){ {0}, {0}, {0}, { 0, 0 }, 0, 0, false }; }
        cakeLayer = 1;
        
        cakeLayer1Type = NO_LAYER;
        icingLayer1Type = NO_LAYER;
        toppingsLayer1Type = NO_LAYER;

        cakeLayer2Type = NO_LAYER;
        icingLayer2Type = NO_LAYER;
        toppingsLayer2Type = NO_LAYER;

        cakeLayer3Type = NO_LAYER;
        icingLayer3Type = NO_LAYER;
        toppingsLayer3Type = NO_LAYER;

        cakeLayer4Type = NO_LAYER;
        icingLayer4Type = NO_LAYER;
        toppingsLayer4Type = NO_LAYER;

        cakeLayer5Type = NO_LAYER;
        icingLayer5Type = NO_LAYER;
        toppingsLayer5Type = NO_LAYER;

        cakeLayer6Type = NO_LAYER;
        icingLayer6Type = NO_LAYER;
        toppingsLayer6Type = NO_LAYER;

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

    if (topping[2].isPressed == true){ renderItem(&topping[2], toppingsSheet); }
    if (topping[1].isPressed == true){ renderItem(&topping[1], toppingsSheet); }
    if (topping[0].isPressed == true){ renderItem(&topping[0], toppingsSheet); }

    // debugging
    // DrawRectangle(cakeHitbox.x, cakeHitbox.y, cakeHitbox.width, cakeHitbox.height, WHITE);
} // end kitchenRender