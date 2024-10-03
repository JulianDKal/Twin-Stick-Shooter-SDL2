#include "Button.h"

void defaultClick()
{
    SDL_LogMessage(0, SDL_LOG_PRIORITY_INFO, "Hey, I was clicked :)");
}

void Button::HandleMouseMotion(const SDL_MouseMotionEvent &e)
{
    bool isHovered{isWithinBounds(e.x, e.y)};
    color = isHovered ? highLightColor : baseColor;
    textColor = isHovered ? textHightLightColor : baseTextColor;
}

void Button::HandleMouseClick(const SDL_MouseButtonEvent& e)
{
    if(isWithinBounds(e.x, e.y)){
        if(!clickHandler) clickHandler = defaultClick;
        clickHandler();
    }
}

void Button::setClickHandler(void (*newClickHandler)())
{
    clickHandler = newClickHandler;
}

void Button::Render()
{
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    
    const char* fontFile = this->textFont.c_str();
    TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    if (!font) {
        std::cerr << "Button failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect textRect;
    if(surface->w < textSurface->w) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "button width too small for text");
    if(surface->h < textSurface->h) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "button height too small for text");
    textRect.x = (surface->w - textSurface->w) / 2;
    textRect.y = (surface->h - textSurface->h) / 2;
    textRect.w = textSurface->w - 20;
    textRect.h = textSurface->h - 20;

    SDL_BlitSurface(textSurface, NULL, surface, &textRect);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    texture = SDL_CreateTextureFromSurface(Game::get().getRenderer(), surface);
    SDL_RenderCopy(Game::get().getRenderer(), texture, NULL, &Rect);
}

void Button::HandleEvent(const SDL_Event &e)
{
    if (e.type == SDL_MOUSEMOTION) {
      //std::cout << "mouse motion event handled" << std::endl;
      HandleMouseMotion(e.motion);
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if(e.button.button == SDL_BUTTON_LEFT){
            HandleMouseClick(e.button);
        }
    }
}

bool Button::isWithinBounds(int x, int y)
{
    // Too far left
    if (x < Rect.x) return false;
    // Too far right
    if (x > Rect.x + Rect.w) return false;
    // Too high
    if (y < Rect.y) return false;
    // Too low
    if (y > Rect.y + Rect.h) return false;
    // Within bounds
    //SDL_LogDebug(0, "is within bounds");
    return true;
}
