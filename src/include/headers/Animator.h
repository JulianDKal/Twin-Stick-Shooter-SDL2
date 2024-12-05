#pragma once
#include <vector>
#include "SDL.h"

class Animator
{
private:
    std::vector<SDL_Texture*> spriteSheets;
public:
    Animator(/* args */);
    ~Animator();
};
