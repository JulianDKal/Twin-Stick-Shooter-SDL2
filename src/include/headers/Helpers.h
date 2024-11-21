#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <math.h>

#define PI 3.14159265358979323846

struct Vector2{
    float x = 0;
    float y = 0;
    void normalize(){
        if(x == 0 && y == 0) return;
        float length = sqrt(pow(x, 2) + pow(y, 2));
        x = x / length;
        y = y / length;
    }
        Vector2 operator*(float scalar) const{
        return Vector2(x * scalar, y * scalar);
    }
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}
    Vector2(){}
};

typedef Vector2 vector2_t;

struct cameraStruct {
    int xPos = 0, yPos = 0;
    int speed = 4;
    vector2_t direction;
};

SDL_Texture* loadTexture(const char* filename );
void drawEntity(SDL_Texture* texture, int x, int y, cameraStruct* cam);
void drawEntity(SDL_Texture *texture, int width, int height, int x, int y, cameraStruct* cam);
void drawEntityRotated(SDL_Texture *texture, int width, int height, float angle, int x, int y, cameraStruct* cam);
float getAngle(int x1, int y1, int x2, int y2);
float calculateDistance(int x1, int y1, int x2, int y2);
SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);