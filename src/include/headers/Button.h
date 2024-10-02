#pragma once
#include <SDL2/SDL.h>
#include "Game.h"
//#include "Text.h"
#include <iostream>

class Button
{
private:
    SDL_Color baseColor, highLightColor;
    SDL_Color color = {0,0,0,0};
    SDL_Color baseTextColor, textHightLightColor;
    SDL_Color textColor = {0,0,0,0};
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect Rect {0, 0, 0, 0};
    std::string text;
    std::string textFont = "./../res/fonts/Vermin Vibes 1989.ttf";
    int fontSize = 40;
    //Text text;
    void HandleMouseMotion(const SDL_MouseMotionEvent& e);
    void HandleMouseClick(const SDL_MouseButtonEvent& e);
    void (*clickHandler)() = nullptr;
public:
    Button(int x, int y, int w, int h, SDL_Color base, SDL_Color highLight, SDL_Color bastTextColor, SDL_Color highLightText, const char* buttonText) 
        : Rect{x - w/2, y - h/2, w, h}, baseColor(base), highLightColor(highLight), baseTextColor(baseTextColor), textHightLightColor(highLightText), text(buttonText) {
            surface = SDL_CreateRGBSurface(0, Rect.w, Rect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
            baseTextColor = {255, 255, 255, 255};
            
        }
    void setClickHandler(void (*newClickHandler)());
    void Render();
    void HandleEvent(const SDL_Event& e);
    bool isWithinBounds(int x, int y);
};
