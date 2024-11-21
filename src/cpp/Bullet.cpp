#include "Bullet.h"

//x and y are the current position of the player, where the bullet is spawned
Bullet::Bullet(int x, int y, cameraStruct* cam)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    direction.x = mouseX - (x - cam->xPos);
    direction.y = mouseY - (y - cam->yPos);
    direction.normalize();

    angle = -90 + getAngle(x - cam->xPos, y - cam->yPos, mouseX, mouseY);

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

void Bullet::draw(cameraStruct* cam)
{
    drawEntityRotated(texture, width, height, angle, xPos, yPos, cam);   
}

void Bullet::updatePositon()
{
    xPos += (int)(speed * direction.x);
    yPos += (int)(speed * direction.y);
    if(this->isOffScreen()) active = false; 
}

