#pragma once
#include "Enemy.h"
#include "Idamageable.h"
#include "AnimationManager.h"

class Ghost : public Enemy
{
public:
    Ghost(int width, int height, const char* textFile) : Enemy(width, height, textFile) {
        this->health = 1;
        this->speed = 5;
        
    };
    void takeDamage(int amount) override {
        Enemy::takeDamage(amount);
    }
};

class BigGhost : public Enemy
{
public:
    BigGhost(int width, int height, const char* textFile, AnimationManager* animManager) : Enemy(width, height, textFile) {
        this->health = 3;
        this->speed = 3;
        //this->animation = std::make_shared<Animation>();
        this->animation = animManager->animations["big_ghost_idle"];
        if(this->animation == nullptr) {
            SDL_Log("Animation not found");
        }
    };
    void takeDamage(int amount) override {
        Enemy::takeDamage(amount);
    }
 };

 class BiggerGhost : public Enemy 
 {
public:
    BiggerGhost(int width, int height, const char* textFile) : Enemy(width, height, textFile) {
        this->health = 5;
        this->speed = 3;
    };
    void takeDamage(int amount) override {
        Enemy::takeDamage(amount);
    }
 };