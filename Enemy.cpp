#include "Enemy.h"

Enemy::Enemy(int width, int height, const char *textFile)
{
    srand(time(NULL));
    int mode = rand() % 4;
    switch (mode)
    {
    case 0:
        xPos = -100;
        yPos = rand() % Game::get().height;
        break;
    case 1:
        xPos = Game::get().width + 100;
        yPos = rand() % Game::get().height;
        break;
    case 2: 
        xPos = rand() % Game::get().width;
        yPos = -100;
        break;
    case 3:
        xPos = rand() % Game::get().width;
        yPos = Game::get().height + 100;
        break;
    default:
        break;
    }
    this->width = width;
    this->height = height;
    texture = loadTexture(textFile);

}

Enemy::~Enemy()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Enemy instance destroyed");
}

void Enemy::updatePosition(int playerPosX, int playerPosY)
{
    if(calculateDistance(xPos, yPos, playerPosX, playerPosY) <= 20){
        active = false;
        Game::get().playerHealth -= 2;
        return;
    }

    direction.x = playerPosX - xPos;
    direction.y = playerPosY - yPos;

    float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    direction.x = direction.x/length;
    direction.y = direction.y/length;

    xPos += (speed * direction.x);
    yPos += (speed * direction.y);

    angle = getAngle(xPos, yPos, playerPosX, playerPosY);
}

void Enemy::draw()
{
    drawEntityRotated(texture, width, height, angle, xPos, yPos);
}