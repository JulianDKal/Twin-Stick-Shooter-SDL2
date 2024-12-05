#include "Helpers.h"

SDL_Texture *loadTexture(const char *filename)
{
    SDL_Texture *texture;

    texture = IMG_LoadTexture(Game::get().getRenderer(), filename);
    if(!texture){
        std::cout << "Error loading texture: " << filename << " SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    else SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loaded %s", filename);

    return texture;
}

void drawEntity(SDL_Texture *texture, int x, int y)
{
    SDL_assert(texture != nullptr);
    SDL_Rect dest;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = x - dest.w/2 - Camera::get().xPos;
    dest.y = y - dest.h/2 - Camera::get().yPos;

    SDL_RenderCopy(Game::get().getRenderer(), texture, NULL, &dest);
}

void drawEntity(SDL_Texture *texture, int width, int height, int x, int y)
{
    SDL_assert(texture != nullptr);
    SDL_Rect dest;

    dest.h = width;
    dest.w = height;

    dest.x = x - width/2 - Camera::get().xPos;
    dest.y = y - height/2 - Camera::get().yPos;
    //SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(Game::get().getRenderer(), texture, NULL, &dest);
}

void drawEntityRotated(SDL_Texture *texture, int width, int height, float angle, int x, int y)
{
    SDL_assert(texture != nullptr);
    SDL_Rect dest;

    dest.h = width;
    dest.w = height;
    dest.x = x - width/2 - Camera::get().xPos;
    dest.y = y - height/2 - Camera::get().yPos;

    SDL_RenderCopyEx(Game::get().getRenderer(), texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void drawEntityFl(SDL_Texture *texture, int width, int height, int x, int y, SDL_RendererFlip flipState)
{
    SDL_assert(texture != nullptr);
    SDL_Rect dest;

    dest.h = width;
    dest.w = height;
    dest.x = x - width/2 - Camera::get().xPos;
    dest.y = y - height/2 - Camera::get().yPos;

    SDL_RenderCopyEx(Game::get().getRenderer(), texture, NULL, &dest, 0, NULL, flipState);
}

//get angle between two points in degrees
float getAngle(int x1, int y1, int x2, int y2)
{
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
    return angle >= 0 ? angle : 360 + angle;

}

float calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return texture;
}

