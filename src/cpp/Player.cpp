#include "Player.h"

void Player::move(int dx, int dy)
{
    xPos = (xPos + dx >= Game::get().width || xPos + dx <= 0 ? xPos : xPos + dx);
    yPos = (yPos + dy >= Game::get().height || yPos + dy <= 0 ? yPos : yPos + dy);
}

void Player::dodge()
{
    if(isDodging) return;
    isDodging = true;
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "dodge started!");
    //Timer timer;
    //timer.setInterval([&]() { endDodge(); }, 1000);
}

void Player::endDodge()
{
    SDL_Log("Dodge is over");
    isDodging = false;
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
