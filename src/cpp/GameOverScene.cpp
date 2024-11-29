#include "GameOverScene.h"

void buttonClick(){
    SceneManager::get().loadScene(SceneManager::get().Gameplay);
}

void GameOverScene::EnterScene()
{
    std::string msg = "Scene entered: " + name;
    SDL_Log(msg.c_str());
    event = new SDL_Event();
    restartButton.setClickHandler(buttonClick);
}

void GameOverScene::UpdateScene()
{
    SDL_RenderClear(Game::get().getRenderer());
    gameOverText.render();
    restartButton.Render();
    SDL_RenderPresent(Game::get().getRenderer());
        while (SDL_PollEvent(event))
        {
        restartButton.HandleEvent(*event);
        switch (event->type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEWHEEL:
                    exit(0);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event->button.button == SDL_BUTTON_LEFT){
                    }
                    break;
                default:
                    break;
            }
        }

    SDL_Delay(16);
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::ExitScene()
{

}
