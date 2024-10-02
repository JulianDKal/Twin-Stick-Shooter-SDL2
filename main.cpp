#include "Game.h"
#include "Helpers.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Text.h"
#include "SceneManager.h"

int main(int argc, char* argv[])
{
    //initializes everything for SDL
    Game& game = Game::get();
    SceneManager& sceneManager = SceneManager::get();

    //SceneManager::get().currentScene = new GameScene();
    sceneManager.loadScene(SceneManager::get().Gameplay);

    while (true)
    {
        sceneManager.currentScene->UpdateScene();
        if(sceneManager.extraScene) sceneManager.extraScene->UpdateScene();
    }

    return EXIT_SUCCESS;
}