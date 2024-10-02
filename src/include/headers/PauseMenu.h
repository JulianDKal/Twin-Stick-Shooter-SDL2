#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"

class PauseMenu : public Scene
{
private:
    SDL_Event* event;
    Button resumeButton = Button(Game::get().width / 2, Game::get().height / 2 + 100, 
            200, 60, transparent, transparent, white, red, "Resume");
    Button exitButton = Button(Game::get().width / 2, Game::get().height / 2 + 150, 
            200, 60, transparent, transparent, white, red, "Exit");
public:
    PauseMenu();
    ~PauseMenu();
    virtual void EnterScene();
    virtual void UpdateScene();
    virtual void ExitScene();
};