#include "Common.h"
#include "Defines.h"
#include "Structs.h"
#include "Keyb.h"

extern int running;

void controlIngame()
{
    if (KEY_IS_PRESSED(KEY_LEFT))
    {

    }
    if (KEY_IS_PRESSED(KEY_RIGHT))
    {

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