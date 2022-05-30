#include "Common.h"
#include "Defines.h"
#include "Draw.h"
#include "Structs.h"
#include "Keyb.h"

extern int running;
extern Sprite sprite_array[];

void controlIngame()
{
    if (KEY_IS_PRESSED(KEY_LEFT) && test.angle > -RAD_360)
    {
        test.angle -= RAD_15;
        //test.texture = rotateTexture(test.angle, &test.texture, TRANSPARENT_COLOR);
    }
    if (KEY_IS_PRESSED(KEY_RIGHT) && test.angle < RAD_360)
    {
        test.angle += RAD_15;
        //test.texture = rotateTexture(test.angle, &test.texture, TRANSPARENT_COLOR);
    }
}

void processInput()
{
    getKeyboard();

    controlIngame();
    
    // F10 always exits, wherever you are
    if (KEY_WAS_HIT(KEY_F10))
        running = 0;

    clearKeys();
}