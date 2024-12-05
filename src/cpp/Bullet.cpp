#include "Bullet.h"

//x and y are the current position of the player, where the bullet is spawned
Bullet::Bullet(int x, int y)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    direction.x = mouseX - (x - Camera::get().xPos);
    direction.y = mouseY - (y - Camera::get().yPos);
    direction.normalize();

    angle = -90 + getAngle(x - Camera::get().xPos, y - Camera::get().yPos, mouseX, mouseY);

    xPos = x;
    yPos = y;
    width = 60;
    height = 60;

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

bool Bullet::isOffScreen()
{
    int width = Game::get().width;
    int height = Game::get().height;
    return xPos >= width || xPos <= 0 || yPos >= height || yPos <= 0;
}

