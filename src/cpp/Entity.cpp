#include "Entity.h"

Entity::Entity(/* args */)
{

}

Entity::Entity(int x, int y, int width, int height, const char *textFile)
{
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    texture = loadTexture(textFile);
}

void Entity::draw()
{
    //drawEntityRotated(texture, width, height, angle, xPos, yPos);
}

bool Entity::isOffScreen()
{
    int width = Game::get().width;
    int height = Game::get().height;
    return xPos >= width || xPos <= 0 || yPos >= height || yPos <= 0;
}

int Entity::getPosX()
{
    return xPos;
}

int Entity::getPosY()
{
    return yPos;
}
