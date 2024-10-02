#include "Player.h"

void Player::move(int dx, int dy)
{
    xPos = (xPos + dx >= Game::get().width || xPos + dx <= 0 ? xPos : xPos + dx);
    yPos = (yPos + dy >= Game::get().height || yPos + dy <= 0 ? yPos : yPos + dy);
}

int Player::getPosX()
{
    return xPos;
}

int Player::getPosY()
{
    return yPos;
}

void Player::draw()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    angle = getAngle(xPos, yPos, mouseX, mouseY);
    drawEntityRotated(texture, width, height, angle, xPos, yPos);
}
