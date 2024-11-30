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
    //textFile can be left empty if you want to create an empty object
    if(textFile != "") texture = loadTexture(textFile);
    else texture = nullptr;
}

void Entity::draw()
{
    //drawEntityRotated(texture, width, height, angle, xPos, yPos);
}

int Entity::getPosX()
{
    return xPos;
}

int Entity::getPosY()
{
    return yPos;
}
