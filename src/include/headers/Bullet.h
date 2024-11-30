#pragma once
#include "Helpers.h"
#include "Entity.h"

class Bullet : public Entity
{
private:
    vector2_t direction;
    float speed = 18;
public:
    bool active = true;
    SDL_Texture* texture;
    void updatePositon();
    bool isOffScreen();
    Bullet(int x, int y);
    ~Bullet();
    virtual void draw();
};

inline bool isInactive(const Bullet& bullet)
{
    return !bullet.active;
}


