#pragma once
#include "Scene.h"
#include "Button.h"
#include "Text.h"
#include "Game.h"
#include "SceneManager.h"

class MainMenu : public Scene
{
private:
    Text gameName = 
        Text(Game::get().width / 2, Game::get().height / 2, "Ghosts and Company", 100, red, "./../res/fonts/Vermin Vibes 1989.ttf", true);
    Button startButton = Button(Game::get().width / 2, Game::get().height / 2 + 100, 200, 60, transparent, transparent, white, red, "Start");
    SDL_Event* event;
public:
    MainMenu(){
        name = "Main Menu";
    }
    virtual void EnterScene();
    virtual void UpdateScene();
    virtual void ExitScene();
    ~MainMenu();
};
