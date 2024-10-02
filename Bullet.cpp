#include "Bullet.h"

//x and y are the current position of the player, where the bullet is spawned
Bullet::Bullet(int x, int y)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    direction.x = mouseX - x;
    direction.y = mouseY - y;
        float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
        direction.x = direction.x/length;
        direction.y = direction.y/length;

    angle = -90 + getAngle(x, y, mouseX, mouseY);

    xPos = x;
    yPos = y;
    width = 40;
    height = 40;

    texture = loadTexture("./../res/bullet.png");
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bullet destroyed");
}

void Bullet::draw()
{
    drawEntityRotated(texture, width, height, angle, xPos, yPos);   
}

void Bullet::updatePositon()
{
    xPos += (int)(speed * direction.x);
    yPos += (int)(speed * direction.y);
    if(this->isOffScreen()) active = false; 
}

