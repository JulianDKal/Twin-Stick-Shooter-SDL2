#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

SDL_Texture *Animation::getFrame()
{
    SDL_Log("Current frame: %d", currentFrame);
    if(counter >= frameTime){
        counter = 0;
        if(currentFrame >= totalFrames - 1){
            currentFrame = 0;
        }
        else {
            currentFrame++;
            SDL_Log("Current frame: %d", currentFrame);}
    }
    else counter++;
    return spriteSheets[currentFrame];
}

void Animation::fillSpriteSheets(std::string filePath)
{
    //TODO: make this dynamic so it also takes in frameHeight, frameWdith and numOfFrames
    int frameWidth = 370, frameHeight = 370, numOfFrames = 4;
    int offsetWidth = 0, offsetHeight = 0;
    frameTime = 10;

    SDL_Log("Loading spritesheet: %s", filePath.c_str());

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load spritesheet: %s", IMG_GetError());
        return;
    }
    //destination surface that gets blitted to
    SDL_Surface* destSurface = SDL_CreateRGBSurface(0, frameWidth, frameHeight, 32, 0, 0, 0, 0);
        if (!destSurface) {
            SDL_Log("Failed to create surface: %s", SDL_GetError());
            return;
        }
    
    for(int i = 0; i < numOfFrames; i++){
        if(offsetWidth * frameWidth >= surface->w){
            offsetWidth = 0;
            offsetHeight++;
        }
        SDL_Rect srcRect = { offsetWidth * frameWidth, offsetHeight * frameHeight, frameWidth, frameHeight };
        SDL_Rect destRect = { 0, 0, frameWidth, frameHeight };
        

        SDL_BlitSurface(surface, &srcRect, destSurface, &destRect);
        //add texture to the vector of frames
        SDL_Texture* frameTexture = SDL_CreateTextureFromSurface(Game::get().getRenderer(), destSurface);
        if (frameTexture == nullptr) {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
            SDL_FreeSurface(destSurface);
            return;
        }
        spriteSheets.push_back(frameTexture);
        offsetWidth++;
    }
    SDL_FreeSurface(surface);
    SDL_FreeSurface(destSurface);
    totalFrames = spriteSheets.size();
}
