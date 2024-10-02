#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <math.h>

#define PI 3.14159265358979323846

struct Vector{
    float x;
    float y;
    void normalize(){
        float length = sqrt(x + y);
        x = x/length;
        y = y/length;
    }
    Vector(float xVal, float yVal) : x(xVal), y(yVal) {}
    Vector(){}
};

typedef Vector vector2;

SDL_Texture* loadTexture(const char* filename );
void drawEntity(SDL_Texture* texture, int x, int y);
void drawEntity(SDL_Texture *texture, int width, int height, int x, int y);
void drawEntityRotated(SDL_Texture *texture, int width, int height, float angle, int x, int y);
float getAngle(int x1, int y1, int x2, int y2);
float calculateDistance(int x1, int y1, int x2, int y2);
SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);