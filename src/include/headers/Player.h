#pragma once
#include "Entity.h"
#include "timercpp.h"

struct Vector2{
    float x = 0;
    float y = 0;

    Vector2(float xVal = 0, float yVal = 0) : x(xVal), y(yVal) {}

    Vector2 operator*(float scalar) const{
        return Vector2(x * scalar, y * scalar);
    }

    void normalize(){
        if(x == 0 && y == 0) return;
        float length = sqrt(pow(x, 2) + pow(y, 2));
        x = x / length;
        y = y / length;
    }
};
typedef struct Vector2 vector2_t;

class Player : public Entity
{
using Entity::Entity;

private:
    int speed = 5, dodgeSpeed = 12;
    //std::atomic<bool> isDodging{false};
    void endDodge();
    //Timer timer;
public:
    bool isDodging = false;
    vector2_t direction;
    void move();
    void dodge();
    int getPosX();
    int getPosY();
    virtual void draw();
};
