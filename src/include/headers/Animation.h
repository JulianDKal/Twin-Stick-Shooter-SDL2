#pragma once 
#include <vector>
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "Game.h"

class Animation{
private:
    int frameTime = 0, counter = 0, currentFrame = 0, totalFrames = 0;
public:
    Animation();
    ~Animation();
    std::vector<SDL_Texture*> spriteSheets;
    SDL_Texture* getFrame();
    void fillSpriteSheets(std::string filePath);
};