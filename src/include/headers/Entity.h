#pragma once
#include "Helpers.h"

class Entity
{
protected:
    int xPos, yPos;
    int width, height;
    float angle = 0;
public:
    SDL_Texture* texture;
    Entity();
    Entity(int x, int y, int width, int height, const char* texFile);
    virtual void draw();
    int getPosX();
    int getPosY();
};

