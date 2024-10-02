#pragma once
#include "Scene.h"
#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "SceneManager.h"

class GameOverScene : public Scene
{
private:
    SDL_Color red = {255, 0, 10, 255};
    SDL_Color transparent = {0,0,0,0};
    SDL_Color white = {255, 255, 255, 255};
    Text gameOverText = Text(Game::get().width / 2, Game::get().height / 2, "Game Over", 110, red, "./../res/fonts/Vermin Vibes 1989.ttf", true);
    SDL_Event* event;
    Button restartButton = Button(Game::get().width / 2, Game::get().height / 2 + 100, 200, 60, transparent, transparent, white, red, "Restart");
public:
    GameOverScene();
    virtual void EnterScene();
    virtual void UpdateScene();
    virtual void ExitScene();
    ~GameOverScene();
};
