#include "UI.h"

void UI::HandleEvent(const SDL_Event &e)
{

}

void UI::Render()
{
    for(auto& button : buttons){
        button.Render();
    }
}

void UI::addButton(const Button &button)
{
    buttons.push_back(button);
}
