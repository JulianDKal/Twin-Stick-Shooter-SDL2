#pragma once
#include "SDL2/SDL.h"
#include <string>
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "Game.h"

class Text
{
private:
    std::string content;
    SDL_Color color;
    std::string font;
    int fontSize;
    int xPos, yPos, width, height;
    SDL_Rect rect {0,0,0,0};
    SDL_Texture* texture;
    bool centered = false;
public:
    Text(int x, int y, std::string content, int fontSize, SDL_Color textColor, std::string pathToFont, bool centered = false);
    ~Text();
    void render();
    void renderRelative(int x, int y);
    void update(std::string content); //creates new texture but does not render
    int getWidth();
    int getHeight();
};



