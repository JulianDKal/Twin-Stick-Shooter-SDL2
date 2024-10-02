#include "PauseMenu.h"

void resumeHandler() {
    SDL_Log("game resumed");
    SceneManager::get().extraScene = nullptr;
    Game::get().paused = false;
}

void exitHandler() {
    SDL_Log("exit game");
}

PauseMenu::PauseMenu(/* args */)
{
    name = "Pause Menu";
}

PauseMenu::~PauseMenu()
{

}

void PauseMenu::EnterScene()
{
    std::string msg = "Scene entered: " + name;
    SDL_Log(msg.c_str());
    event = new SDL_Event();
    resumeButton.setClickHandler(resumeHandler);
    exitButton.setClickHandler(exitHandler);
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
    //SDL_RenderClear(Game::get().getRenderer());

    //SDL_SetRenderDrawColor(Game::get().getRenderer(), 255, 255, 255, 255); //reset drawing color
    resumeButton.Render();
    exitButton.Render();
    SDL_RenderPresent(Game::get().getRenderer());
    SDL_Delay(16);
}

void PauseMenu::ExitScene()
{

}
