#pragma once
#include "Enemy.h"
#include "Idamageable.h"

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
