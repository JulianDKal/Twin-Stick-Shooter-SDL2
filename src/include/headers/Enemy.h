#pragma once
#include "Entity.h"
#include <random>
#include "Idamageable.h"

class Game;

class Enemy : public Entity, public Idamageable
{
protected:
    int speed = 4;
    int health = 1;
    SDL_RendererFlip flipState = SDL_FLIP_NONE;
    vector2_t direction;
public:
    bool active = true;
    Enemy(int width, int height, const char* textFile);
    ~Enemy();
    virtual void updatePosition(int playerPosX, int playerPosY);
    void draw(int playerX, int playerY);
    void takeDamage(int amount){
        health -= amount;
        if(health <= 0) {
            this->active = false;
            Game::get().score += 1;
        }
    }
};