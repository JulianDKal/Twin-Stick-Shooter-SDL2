#include "Player.h"

void Player::move()
{
    direction.normalize();
    direction = direction * speed;

    xPos = (xPos + direction.x >= Game::get().width || xPos + direction.x <= 0 ? xPos : xPos + direction.x);
    yPos = (yPos + direction.y >= Game::get().height || yPos + direction.y <= 0 ? yPos : yPos + direction.y);
    direction.x = 0;
    direction.y = 0;
}

void Player::dodge()
{
    if(isDodging) return;
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Dodge started!");
    isDodging = true;

    std::thread t([=, this]() {
        if(!isDodging) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(!isDodging) return;
        endDodge();
    });
    t.detach();
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
