#pragma once
#include "SDL2/SDL.h"
#include <string>

class Scene
{
protected:
    SDL_Color red = {255, 0, 10, 255};
    SDL_Color transparent = {0,0,0,0};
    SDL_Color white = {255, 255, 255, 255};
public:
    std::string name = "";
    virtual void EnterScene() = 0;
    virtual void UpdateScene() = 0;
    virtual void ExitScene() = 0;
    virtual ~Scene() = default;
};

