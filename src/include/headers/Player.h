#pragma once
#include "Entity.h"
#include "timercpp.h"
#include "Helpers.h"

class Player : public Entity
{
using Entity::Entity;

private:
    int speed = 5, dodgeSpeed = 16;
    vector2_t dodgeDirection;
    void endDodge();
    //Timer timer;
public:
    bool isDodging = false;
    vector2_t direction;
    void move();
    void dodge();
    int getPosX();
    int getPosY();
    virtual void draw(cameraStruct* cam);
};
