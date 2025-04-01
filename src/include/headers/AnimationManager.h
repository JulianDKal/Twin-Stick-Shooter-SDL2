#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "SDL.h"
#include "Animation.h"
#include <filesystem>
#include "JsonParser.h"

class AnimationManager
{
private:
    //this method is called at the beginning and creates an animation for each entry in the spritesheets folder
    void addAnimations(std::string spiritSheetPath);
    //std::vector<SDL_Texture*> spriteSheets;
    int currentFrame = 0;
public:
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> getAnimation(std::string animationName);
    AnimationManager();
    ~AnimationManager();
};
