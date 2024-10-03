#include "Player.h"

void Player::move()
{
    if(!isDodging){
        direction.normalize();
        direction = direction * speed;

        xPos = (xPos + direction.x >= Game::get().width || xPos + direction.x <= 0 ? xPos : xPos + direction.x);
        yPos = (yPos + direction.y >= Game::get().height || yPos + direction.y <= 0 ? yPos : yPos + direction.y);
    }
    else {
        xPos = (xPos + dodgeDirection.x >= Game::get().width || xPos + dodgeDirection.x <= 0 ? xPos : xPos + dodgeDirection.x);
        yPos = (yPos + dodgeDirection.y >= Game::get().height || yPos + dodgeDirection.y <= 0 ? yPos : yPos + dodgeDirection.y);
    }
    
    direction.x = 0;
    direction.y = 0;
}

void Player::dodge()
{
    if(isDodging) return;
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Dodge started!");
    //This is horrible
    dodgeDirection = direction;
    dodgeDirection.normalize();
    dodgeDirection = dodgeDirection * dodgeSpeed;
    isDodging = true;
    SDL_SetTextureColorMod(texture, 100, 100, 255); //multiplies the texture with a blue-ish color
    SDL_SetTextureAlphaMod(texture, 200); //lowers alpha value of the texture

    std::thread t([=, this]() {
        if(!isDodging) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if(!isDodging) return;
        endDodge();
    });
    t.detach();
}

void Player::endDodge()
{
    SDL_Log("Dodge is over");
    isDodging = false;
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(texture, 255);
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
