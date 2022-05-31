#include "Common.h"
#include "Defines.h"
#include "Enums.h"
#include "Structs.h"

/* Graphics drawing functions */

extern uint8_t far screen_buf [];
extern Sprite sprite_array[];
extern Texture Textures[];

int boundaryCheck(int x, int y)
{
    if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0)
        return TRUE;
    else
        return FALSE;
}

int boundaryCheck_X(int x)
{
    if (x < SCREEN_WIDTH && x >= 0)
        return TRUE;
    else
        return FALSE;
}

int boundaryCheck_Y(int y)
{
    if (y < SCREEN_HEIGHT && y >= 0)
        return TRUE;
    else
        return FALSE;
}

void drawSprite(int x, int y, Texture* texture)
{
    int pix_x = x;
    int pix_y = y;
    int index_x;
    int index_y;
    int i = 0;

    if (texture->transparent == TRUE)
    {
        for (index_y = 0; index_y < texture->height; index_y++)
        {
            for (index_x = 0; index_x < texture->width; index_x++)
            {
                if (texture->pixels[i] != TRANSPARENT_COLOR)
                {
                    if (pix_x < SCREEN_WIDTH && pix_y < SCREEN_HEIGHT)
                    {
                        SET_PIXEL(pix_x, pix_y, texture->pixels[i]);
                        i++;
                        pix_x++;
                    }
                    else
                    {
                        i++;
                        pix_x++;
                    }
                }
                else
                {
                    i++;
                    pix_x++;
                }
            }
            pix_x = x;
            pix_y++;
        }
    }
    else
    {
        for (index_y = 0; index_y < texture->height; index_y++)
        {
            for (index_x = 0; index_x < texture->width; index_x++)
            {
                if (pix_x < SCREEN_WIDTH && pix_x >= 0 && pix_y < SCREEN_HEIGHT && pix_y >= 0)
                {
                    SET_PIXEL(pix_x, pix_y, texture->pixels[i]);
                    i++;
                    pix_x++;
                }
                else
                {
                    i++;
                    pix_x++;
                }
            }
            pix_x = x;
            pix_y++;
        }
    }
}

float rotateShearX(Vec2 source, double angle)
{
    float new_loc;

    new_loc = source.x - tan(angle / 2) * source.y;

    new_loc = (int)new_loc;

    return new_loc;
}

float rotateShearY(Vec2 source, double angle)
{
    float new_loc;

    new_loc = source.y + sin(angle) * source.x;

    new_loc = (int)new_loc;

    return new_loc;
}

Vec2 multiplyMatrixVec2(float matrix_x[4], float matrix_y[4], Vec2 v)
{
   Vec2 result;
   float temp_matrix[4]; // saves the current result of matrix multiplications

   temp_matrix[0] = (matrix_x[0] * matrix_y[0]) + (matrix_x[1] * matrix_y[2]);
   temp_matrix[1] = (matrix_x[0] * matrix_y[1]) + (matrix_x[1] * matrix_y[3]);
   temp_matrix[2] = (matrix_x[2] * matrix_y[0]) + (matrix_x[3] * matrix_y[2]);
   temp_matrix[3] = (matrix_x[2] * matrix_y[1]) + (matrix_x[3] * matrix_y[3]);
   
   temp_matrix[0] = (temp_matrix[0] * matrix_x[0]) + (temp_matrix[1] * matrix_x[2]);
   temp_matrix[1] = (temp_matrix[0] * matrix_x[1]) + (temp_matrix[1] * matrix_x[3]);
   temp_matrix[2] = (temp_matrix[2] * matrix_x[0]) + (temp_matrix[3] * matrix_x[2]);
   temp_matrix[3] = (temp_matrix[2] * matrix_x[1]) + (temp_matrix[3] * matrix_x[3]);

   result.x = temp_matrix[0] * v.x + temp_matrix[1] * v.y;
   result.y = temp_matrix[2] * v.x + temp_matrix[3] * v.y;

   return result;
}

Vec2 shearMatrixVec2(float matrix[4], Vec2 v)
{
   Vec2 result;

   result.x = matrix[0] * v.x + matrix[1] * v.y;
   result.y = matrix[2] * v.x + matrix[3] * v.y;

   result.x = (int)result.x;
   result.y = (int)result.y;

   return result;
}

Texture rotateTexture(double angle, Texture* source, uint8_t bgcolor)
{
    Texture rotated;
    Vec2 sheared;
    int w;
    int h;
    int w_half;
    int h_half;
    int i = 0;
    float rot_i;
    int rotated_size;
    float theta_t;
    float theta_s;
    float matrix_x[4] = {1.0, 0.0, 0.0, 1.0};
    float matrix_y[4] = {1.0, 0.0, 0.0, 1.0};

    if (angle > RAD_270)
        angle -= RAD_360;

    else if (angle < -RAD_270)
        angle += RAD_360;

    if (angle > RAD_90)
    {
        angle -= RAD_180;
        source->mirrorFlip = TRUE;
    }

    else if (angle < -RAD_90)
    {
        angle += RAD_180;
        source->mirrorFlip = TRUE;
    }

    theta_t = -(tan(angle / 2));
    theta_s = sin(angle);

    matrix_x[1] = theta_t;
    matrix_y[2] = theta_s;
 
    rotated.width = abs(source->height * sin(angle)) + abs(source->width * cos(angle)) + 2;
    rotated.height = abs(source->width * sin(angle)) + abs(source->height * cos(angle)) + 2;

    source->offset_x = (rotated.width - source->width) / 2;
    source->offset_y = (rotated.height - source->height) / 2;

    w_half = source->width / 2;
    h_half = source->height / 2;

    rotated.pixels = malloc(rotated.width * rotated.height);
    rotated_size = rotated.width * rotated.height;
    memset(rotated.pixels, bgcolor, rotated_size);

    if (source->mirrorFlip == TRUE)
    {
        for (h = -h_half; h < h_half; h++)
        {
            for (w = -w_half; w < w_half; w++)
            {
                sheared.x = w;
                sheared.y = h;
                sheared.x = rotateShearX(sheared, angle);
                sheared.y = rotateShearY(sheared, angle);
                sheared.x = rotateShearX(sheared, angle);
                rot_i = ((rotated.height - ((int)sheared.y + source->offset_y + h_half))) * rotated.width + (rotated.width - (sheared.x + source->offset_x + w_half));
                rotated.pixels[(int)rot_i] = source->pixels[i];
                i++;
            }
        }
    }
    else
    {
        for (h = -h_half; h < h_half; h++)
        {
            for (w = -w_half; w < w_half; w++)
            {
                sheared.x = w;
                sheared.y = h;
                sheared.x = rotateShearX(sheared, angle);
                sheared.y = rotateShearY(sheared, angle);
                sheared.x = rotateShearX(sheared, angle);
                rot_i = ((int)sheared.y + source->offset_y + h_half) * rotated.width + (sheared.x + source->offset_x + w_half);
                rotated.pixels[(int)rot_i] = source->pixels[i];
                i++;
            }
        }
    }

    return rotated;
}

void drawRectangle(int x, int y, int w, int h, uint8_t color)
{
    int index_x = 0;
    int index_y = 0;

    for (index_y = 0; index_y < h; index_y++)
    {
        for (index_x = 0; index_x < w; index_x++)
        {
            SET_PIXEL(x, y, color);
            x++;
        }
        index_x = 0;
        x -= w;
        y++;
    }
    index_y = 0;
}

void drawStuff()
{
    char angle_str [20];
    float deg_angle = radToDeg(test.angle);
    //test.angle -= RAD_15;
    sprintf(angle_str, "ANGLE: %f", deg_angle);
    drawText(65, 75, angle_str, COLOR_WHITE);
    test.texture = rotateTexture(test.angle, &Textures[BRICKS], TRANSPARENT_COLOR);
    drawSprite(test.x, test.y, &test.texture);
}