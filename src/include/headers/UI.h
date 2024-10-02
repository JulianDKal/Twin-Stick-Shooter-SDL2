#pragma once
#include "SDL2/SDL.h"
#include "Button.h"
#include <list>

class UI
{
private:
    std::list<Button> buttons;
public:
    void HandleEvent(const SDL_Event& e);
    void Render();
    void addButton(const Button& button);
};

