#include "PauseMenu.h"

void PauseMenu::resumeHandler() {
    SDL_Log("game resumed");
    SceneManager::get().extraScene = nullptr;
    Game::get().paused = false;
}

void PauseMenu::exitHandler() {
    SDL_Log("return to main menu");
    SceneManager::get().extraScene = nullptr;
    Game::get().paused = false;
    resumeButton.reset();
    exitButton.reset();
    SceneManager::get().loadScene(SceneManager::get().Menu);
}

PauseMenu::PauseMenu(/* args */)
{
    name = "Pause Menu";
    SDL_Log("Pause menu constructed");
}

void PauseMenu::EnterScene()
{
    SDL_Log("Scene entered: %s", name.c_str());
    event = new SDL_Event();
    resumeButton.setClickHandler(std::bind(&PauseMenu::resumeHandler, this));
    exitButton.setClickHandler(std::bind(&PauseMenu::exitHandler, this));
}

void PauseMenu::UpdateScene()
{
    while (SDL_PollEvent(event))
        {
        resumeButton.HandleEvent(*event);
        exitButton.HandleEvent(*event);
        switch (event->type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEWHEEL:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    if(event->key.keysym.sym == SDLK_ESCAPE){
                        resumeHandler();
                    }
                    break;
                default:
                    break;
            }
        }
    SDL_SetRenderDrawBlendMode(Game::get().getRenderer(), SDL_BLENDMODE_BLEND);
    
    SDL_SetRenderDrawColor(Game::get().getRenderer(), 0, 0, 0, 128); // RGBA, with 128 being 50% opacity
    SDL_Rect screenRect = {0, 0, Game::get().width, Game::get().height};
    SDL_RenderFillRect(Game::get().getRenderer(), &screenRect);

    resumeButton.Render();
    exitButton.Render();
    SDL_RenderPresent(Game::get().getRenderer());
    SDL_Delay(16);
}

void PauseMenu::ExitScene()
{

}

PauseMenu::~PauseMenu()
{

}
