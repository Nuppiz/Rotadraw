#ifndef DRAW_H
#define DRAW_H

#include "Structs.h"

void drawSprite(int x, int y, Texture* texture);
Texture rotateTexture(int angle, Texture* source, uint8_t bgcolor);
void drawStuff();

#endif /* DRAW_H */
