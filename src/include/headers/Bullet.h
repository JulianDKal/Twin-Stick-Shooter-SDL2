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
    Bullet(int x, int y, cameraStruct* cam);
    ~Bullet();
    virtual void draw(cameraStruct* cam);
};

inline bool isInactive(const Bullet& bullet)
{
    return !bullet.active;
}


