#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"

class PauseMenu : public Scene
{
private:
    SDL_Event* event;
    Button resumeButton = Button(Game::get().width / 2, Game::get().height / 2 + 120, 
            300, 100, transparent, transparent, white, red, "Resume", 70);
    Button exitButton = Button(Game::get().width / 2, Game::get().height / 2 + 210, 
            300, 100, transparent, transparent, white, red, "Exit", 70);
public:
    PauseMenu();
    ~PauseMenu();
    virtual void EnterScene();
    virtual void UpdateScene();
    virtual void ExitScene();

    void resumeHandler();
    void exitHandler();
};