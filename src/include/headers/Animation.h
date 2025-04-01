#pragma once 
#include <vector>
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "Game.h"

class Animation{
public:
    bool looping = true;
    int frameTime = 0, counter = 0, currentFrame = 0, totalFrames = 0;
    Animation();
    ~Animation();
    std::vector<SDL_Texture*> spriteSheets;
    SDL_Texture* getFrame();
    void fillSpriteSheets(std::string filePath);
};