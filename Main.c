#include "Common.h"
#include "Defines.h"
#include "Draw.h"
#include "Enums.h"
#include "Input.h"
#include "Loadgfx.h"
#include "Structs.h"
#include "Text.h"
#include "Video.h"

int running = 1;
extern Texture Textures[];
Sprite sprite_array[1];

void quit()
{   
    deinitKeyboard();
    setMode(TEXT_MODE);
}

void main()
{
    setMode(VGA_256_COLOR_MODE);
    initKeyboard();
    loadFont();
    loadAllTextures();

    sprite_array[0].texture = Textures[BRICKS];
    sprite_array[0].x = 140;
    sprite_array[0].y = 90;
    sprite_array[0].angle = RAD_15;
    Textures[BRICKS].mirrorFlip = FALSE;
    
    while (running == 1)
    {
        processInput();
        drawStuff();
        render();
        delay(50);
    }
    quit();
}