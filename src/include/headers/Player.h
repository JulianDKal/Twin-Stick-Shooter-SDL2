#pragma once
#include "Entity.h"

class Player : public Entity
{
using Entity::Entity;

private:
    int speed = 5;
public:
    void move(int dx, int dy);
    int getPosX();
    int getPosY();
    virtual void draw();
};


