#include "SceneManager.h"

//SceneManager SceneManager::instance;

void SceneManager::loadScene(SCENE_NAME scene)
{
    if(currentScene) currentScene->ExitScene();
    currentScene = (scenes[scene]);
    currentScene->EnterScene();
}

void SceneManager::loadSceneAdditive(SCENE_NAME scene)
{
    extraScene = scenes[scene];
    extraScene->EnterScene();
}

SceneManager::~SceneManager()
{
}

SceneManager::SceneManager() : currentScene(nullptr), extraScene(nullptr) {
    SDL_Log("SceneManager constructor called!");
    scenes[Pause] = new PauseMenu();
    scenes[Menu] = new MainMenu();
    scenes[Gameplay] = new GameScene(); 
    scenes[GameOver] = new GameOverScene(); 
}