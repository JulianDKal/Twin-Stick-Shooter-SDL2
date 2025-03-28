#pragma once
#include "Helpers.h"
#include "Animation.h"
#include "memory"

class Entity
{
protected:
    int xPos, yPos;
    int width, height;
    float angle = 0;
    std::shared_ptr<Animation> animation = nullptr;
public:
    SDL_Texture* texture;
    Entity();
    Entity(int x, int y, int width, int height, const char* texFile);
    virtual void draw();
    virtual void enterAnimation();
    int getPosX();
    int getPosY();
};

