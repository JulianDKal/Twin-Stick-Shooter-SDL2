#pragma once
#include "Entity.h"
#include <random>
#include <time.h>
#include "Idamageable.h"

class Game;

class Enemy : public Entity, public Idamageable
{
private:
    int speed = 4;
    int health = 1;
    vector2_t direction;
public:
    bool active = true;
    Enemy(int width, int height, const char* textFile);
    ~Enemy();
    void updatePosition(int playerPosX, int playerPosY);
    void draw();
    void takeDamage(int dmg){
        health -= dmg;
        if(health <= 0) this->active = false;
    }
};

inline bool isDead(const Enemy& enemy)
{
    return !enemy.active;
}
