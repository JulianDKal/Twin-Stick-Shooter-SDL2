#pragma once
#include "Helpers.h"

class Entity
{
protected:
    int xPos, yPos;
    int width, height;
    float angle = 0;
    SDL_Texture* texture;
public:
    Entity();
    Entity(int x, int y, int width, int height, const char* texFile);
    virtual void draw();
    int getPosX();
    int getPosY();
};

