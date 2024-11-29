#include "MainMenu.h"

void startGame()
{
    SceneManager::get().loadScene(SceneManager::get().Gameplay);
}

void MainMenu::EnterScene()
{
    event = new SDL_Event();
    startButton.setClickHandler(startGame);
    SDL_Log("Entered Scene: %s", name.c_str());
}

void MainMenu::UpdateScene()
{
    SDL_RenderClear(Game::get().getRenderer());
    gameName.render();
    startButton.Render();
    SDL_RenderPresent(Game::get().getRenderer());

    while (SDL_PollEvent(event))
        {
        startButton.HandleEvent(*event);
        switch (event->type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEWHEEL:
                    exit(0);
                    break;
                default:
                    break;
            }
        }

    SDL_Delay(16);
}

void MainMenu::ExitScene()
{
    startButton.reset();
}

MainMenu::~MainMenu()
{
}