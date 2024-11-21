#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <list>

#ifndef PLAYER_HEALTH
#define PLAYER_HEALTH 2
#endif

class Game
{
private:
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    Game();
public:
    //Game* Game::instance = NULL;

    int playerHealth = PLAYER_HEALTH;
    int score = 0;
    int width, height;
    bool paused = false;
    static Game& get(){
        static Game instance;
        return instance;
    }
    ~Game();
    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer();

    Game(Game& other) = delete;
    void operator=(const Game& other) = delete;
};


