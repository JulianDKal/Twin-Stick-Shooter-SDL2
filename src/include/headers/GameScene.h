#pragma once
#include "Scene.h"
#include "SDL2/SDL.h"
#include "Player.h"
#include "Text.h"
#include "Button.h"
#include "Bullet.h"
#include "Camera.h"
#include "SceneManager.h"
#include <list>
#include "EnemyTypes.h"
#include <memory>

class GameScene : public Scene
{
//using Scene::Scene;
private:
    std::list<Bullet> bullets;
    std::list<std::unique_ptr<Enemy>> enemies;
    SDL_Event* event;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color transparent = {0,0,0,0};
    Player player;
    bool charging = false;
    int charge = 0;
    Uint32 lastShotTime = 0;
    Uint32 lastSpawnTimeGhost = 0, bigGhostTime = 0;
    Uint32 ghostSpawnTimeSave, bigGhostTimeSave;
    SDL_Texture* background;
    Text scoreText = Text(10, 10, "Score: " + std::to_string(Game::get().score),40, white, "./../res/fonts/Vermin Vibes 1989.ttf");
    Text healthText = Text(scoreText.getWidth() + 25, 10, "Health: " + std::to_string(Game::get().playerHealth), 
        40, white, "./../res/fonts/Vermin Vibes 1989.ttf");
    int chargeRectPosX = scoreText.getWidth() + healthText.getWidth() + 50;
    int chargeRectPosY = 15;
    SDL_Rect chargeRect {chargeRectPosX, chargeRectPosY, 10, 20};
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
};


