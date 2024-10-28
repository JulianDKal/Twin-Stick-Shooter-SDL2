#include "Text.h"

Text::Text(int x, int y, std::string content, int fontSize, SDL_Color textcolor, std::string pathToFont, bool centered)
{
    this->content = content;
    this->fontSize = fontSize;
    color = textcolor;
    this->font = pathToFont;

    xPos = x;
    yPos = y;

    const char* fontFile = this->font.c_str();
    TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, content.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    texture = SDL_CreateTextureFromSurface(Game::get().getRenderer(), surface);
    if (!texture) {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    if(!centered) rect = {xPos, yPos, width, height};
    else rect = {xPos - width/2, yPos - height/2, width, height};
}

Text::~Text()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void Text::render()
{
    SDL_RenderCopy(Game::get().getRenderer(), texture, NULL, &rect);
}

void Text::renderRelative(int x, int y)
{
    rect.x = xPos - x;
    rect.y = yPos - y;
    SDL_RenderCopy(Game::get().getRenderer(), texture, NULL, &rect);
}

void Text::update(std::string content)
{
    this->content = content;

    const char* fontFile = this->font.c_str();
    TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, content.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    texture = SDL_CreateTextureFromSurface(Game::get().getRenderer(), surface);
    if (!texture) {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    if(!centered) rect = {xPos, yPos, width, height};
    else rect = {xPos - width/2, yPos - height/2, width, height};
}

int Text::getWidth()
{
    return width;
}

int Text::getHeight()
{
    return height;
}
