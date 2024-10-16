#pragma once
#include "Scene.h"
#include "SDL2/SDL.h"
#include "timercpp.h"
#include "Player.h"
#include "Text.h"
#include "Button.h"
#include "Bullet.h"
#include "Enemy.h"
#include "SceneManager.h"

class GameScene : public Scene
{
//using Scene::Scene;
private:
    const int WIDTH = 1000;
    const int HEIGHT = 580;
    SDL_Rect render_viewport {0,0,WIDTH - 100, HEIGHT - 100};
    Timer timer;
    std::list<Bullet> bullets;
    std::list<Enemy> enemies;
    SDL_Event* event;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color transparent = {0,0,0,0};
    Player player;
    bool mouseDown, charging = false;
    int charge = 0;
    int mouseCounter = 0;
    SDL_Texture* background = loadTexture("./../res/background.jpg");
    Text scoreText = Text(10, 10, "Score: " + std::to_string(Game::get().score),40, white, "./../res/fonts/Vermin Vibes 1989.ttf");
    Text healthText = Text(scoreText.getWidth() + 25, 10, "Health: " + std::to_string(Game::get().playerHealth), 
        40, white, "./../res/fonts/Vermin Vibes 1989.ttf");
    SDL_Rect chargeRect {scoreText.getWidth() + healthText.getWidth() + 50, 15, 10, 20};
    SDL_Color red = {255, 0, 10, 255};
public:
    GameScene(/* args */);
    ~GameScene();
    virtual void EnterScene();
    virtual void UpdateScene();
    virtual void ExitScene();
    void UpdateGame();
    void RenderGame();
    void doInput(SDL_Event* event);
    void spawnEnemy();
};


