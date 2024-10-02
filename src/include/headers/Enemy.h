#pragma once
#include "Entity.h"
#include <random>
#include <time.h>

class Game;

class Enemy : public Entity
{
private:
    int speed = 4;
    vector2 direction;
public:
    bool active = true;
    Enemy(int width, int height, const char* textFile);
    ~Enemy();
    void updatePosition(int playerPosX, int playerPosY);
    void draw();
};

inline bool isDead(const Enemy& enemy)
{
    return !enemy.active;
}
