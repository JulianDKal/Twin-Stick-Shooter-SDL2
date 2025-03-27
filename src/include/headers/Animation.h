#pragma once 
#include <vector>
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "Game.h"

class Animation{
private:
    int frameRate, currentFrame = 0, totalFrames;
public:
    Animation();
    ~Animation();
    std::vector<SDL_Texture*> spriteSheets;
    SDL_Texture* getFrame();
    void playNextFrame();
    void fillSpriteSheets(std::string filePath);
};