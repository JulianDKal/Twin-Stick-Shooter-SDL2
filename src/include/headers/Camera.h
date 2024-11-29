#pragma once
#include "Game.h"

class Camera
{
private:
    Camera(); //prevent direct instantiation
public:
    int xPos = 0, yPos = 0;
    static Camera& get(){
        static Camera instance;
        return instance;
    }
    void update(int playerX, int playerY);
    void setPos(int x, int y);
};
