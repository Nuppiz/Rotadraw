#include "Common.h"
#include "Structs.h"
#include "Defines.h"
#include "Draw.h"
#include "Input.h"
#include "Loadgfx.h"
#include "Text.h"
#include "Video.h"

int running = 1;

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
    
    while (running == 1)
    {
        processInput();
        render();
        drawStuff();
        delay(50);
    }
    quit();
}