#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    int x, y;
} Vec2_int;

typedef struct
{
    uint8_t r,g,b;
} Color;

typedef struct
{
    Color colors[256];
} Palette;

typedef struct
{
    uint8_t* pixels;
    uint16_t height;
    uint16_t width;
    uint16_t transparent;
    uint8_t mirrorFlip;
} Texture;

typedef struct
{
    Texture texture;
    int x, y;
    double angle;
} Sprite;

#endif