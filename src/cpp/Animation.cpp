#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::fillSpriteSheets(std::string filePath)
{
    //TODO: make this dynamic so it also takes in frameHeight, frameWdith and numOfFrames
    int frameWidth = 370, frameHeight = 370, numOfFrames = 4;
    int offsetWidth = 0, offsetHeight = 0;

    SDL_Log("Loading spritesheet: %s", filePath.c_str());

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load spritesheet: %s", IMG_GetError());
        return;
    }
    //destination surface that gets blitted to
    
    for(int i = 0; i < numOfFrames; i++){
        if(offsetWidth * frameWidth >= surface->w){
            offsetWidth = 0;
            offsetHeight++;
        }
        SDL_Rect srcRect = { offsetWidth * frameWidth, offsetHeight * frameHeight, frameWidth, frameHeight };
        SDL_Rect destRect = { 0, 0, frameWidth, frameHeight };
        SDL_Surface* destSurface = SDL_CreateRGBSurface(0, frameWidth, frameHeight, 32, 0, 0, 0, 0);
        if (!destSurface) {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return;
        }

        SDL_BlitSurface(surface, &srcRect, destSurface, &destRect);
        //add surface to the vector of frames
        if(Game::get().getRenderer() == nullptr) {
            SDL_Log("Renderer is null");
            return;
        }
        spriteSheets.push_back(SDL_CreateTextureFromSurface(Game::get().getRenderer(), destSurface));
    }
    SDL_FreeSurface(surface);
}
