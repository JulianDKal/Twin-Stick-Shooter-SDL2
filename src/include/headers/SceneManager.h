#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "PauseMenu.h"
#include "MainMenu.h"

class SceneManager
{
private:
    Scene* scenes[4];
    SceneManager();  
public:
    SceneManager(const SceneManager&) = delete;
    static SceneManager& get(){
        static SceneManager instance;
        return instance;
    }
    //GameScene* gameScene {new GameScene};
    Scene* currentScene;
    Scene* extraScene;
    enum SCENE_NAME {
        Pause = 0,
        Menu = 1,
        Gameplay,
        GameOver
    };
    //GameScene* gS;

    void loadScene(SCENE_NAME scene);
    void loadSceneAdditive(SCENE_NAME scene);
    ~SceneManager();
};
