#include "Player.h"

Uint32 dodgeCallback(Uint32 interval, void* param){
    Player* player = static_cast<Player*>(param);
    SDL_Log("Dodge is over");
    player->isDodging = false;
    SDL_SetTextureColorMod(player->texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(player->texture, 255);

    return 0;
}

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
    SDL_TimerID timer = SDL_AddTimer(200, dodgeCallback, this);
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Dodge started!");
    
    dodgeDirection = direction;
    dodgeDirection.normalize();
    dodgeDirection = dodgeDirection * dodgeSpeed;
    isDodging = true;
    SDL_SetTextureColorMod(texture, 100, 100, 255); //multiplies the texture with a blue-ish color
    SDL_SetTextureAlphaMod(texture, 200); //lowers alpha value of the texture
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
    angle = getAngle(xPos - Camera::get().xPos, yPos - Camera::get().yPos, mouseX, mouseY);
    drawEntityRotated(texture, width, height, angle, xPos, yPos);
}

