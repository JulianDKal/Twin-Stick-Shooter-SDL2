#include "AnimationManager.h"

void AnimationManager::addAnimations(std::string spiritSheetPath)
{
    for(auto& entry : std::filesystem::directory_iterator(spiritSheetPath)){
        SDL_Log("Found file: %s", entry.path().string().c_str());
        if(entry.path().extension() == ".png"){
            std::string fileName = entry.path().filename().string();
            std::string animationName = fileName.substr(0, fileName.find_last_of('.'));
            animations[animationName] = std::make_shared<Animation>();
            animations[animationName]->fillSpriteSheets(entry.path().string());
            SDL_Log("Animation added: %s with %d frames", animationName.c_str(), animations[animationName]->spriteSheets.size());
        }
    }
}

AnimationManager::AnimationManager(/* args */)
{
    addAnimations("./../res/spritesheets/");
}

AnimationManager::~AnimationManager()
{
}