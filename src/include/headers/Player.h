#pragma once
#include "Entity.h"
#include "timercpp.h"

class Player : public Entity
{
using Entity::Entity;

private:
    int speed = 5, dodgeSpeed = 12;
    //std::atomic<bool> isDodging{false};
    bool isDodging = false;
    void endDodge();
    //Timer timer;
public:
    void move(int dx, int dy);
    void dodge();
    int getPosX();
    int getPosY();
    virtual void draw();
};
