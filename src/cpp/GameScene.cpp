#include "GameScene.h"

GameScene::GameScene(/* args */)
{
    name = "Game Scene";
}

GameScene::~GameScene()
{
}

void GameScene::EnterScene()
{
    std::string msg = "Scene entered: " + name;
    SDL_Log(msg.c_str());
    event = new SDL_Event;
    
    player = Player(WIDTH / 2, HEIGHT/2, 70, 70, "./../res/spaceship.png");
    SDL_Texture* backgound = loadTexture("./../res/background.jpg");

    timer.setInterval([&]() { spawnEnemy(); }, 2000);
}

void GameScene::UpdateScene()
{
    if(!Game::get().paused) UpdateGame();
    RenderGame();
}

void GameScene::ExitScene()
{
    Game::get().playerHealth = PLAYER_HEALTH;
    Game::get().score = 0;
    Game::get().up = 0; Game::get().down = 0; Game::get().left = 0; Game::get().right = 0;
    for(auto& enemy : enemies){
        enemy.active = false;
        //enemy.~Enemy();
    }
    timer.stopTimer();
}

void GameScene::UpdateGame()
{
        doInput(event);
        if(mouseDown && !(mouseCounter % 10)) bullets.emplace_back(player.getPosX(), player.getPosY());

        if(player.isDodging){

        }
        else {
            player.move();
        }

        scoreText.update("Score: " + std::to_string(Game::get().score));
        healthText.update("Health: " + std::to_string(Game::get().playerHealth));

        bullets.remove_if(isInactive);
        enemies.remove_if(isDead);

        //Check for bullet and enemy collision
        for(auto& bullet : bullets) {
            for(auto& enemy : enemies) {
                if(calculateDistance(bullet.getPosX(), bullet.getPosY(), enemy.getPosX(), enemy.getPosY()) <= 35){
                    enemy.active = false;
                    bullet.active = false;
                    Game::get().score += 1;
                }
            }
        }

        for(auto& bullet : bullets) {
            bullet.updatePositon();
        }
        for(auto& enemy : enemies) {
            enemy.updatePosition(player.getPosX(), player.getPosY());
        }
        if(Game::get().playerHealth <= 0) SceneManager::get().loadScene(SceneManager::get().GameOver);
}

void GameScene::RenderGame()
{
        //Actual Drawing happens here
        SDL_RenderClear(Game::get().getRenderer());
        SDL_RenderCopy(Game::get().getRenderer(), background, NULL, NULL);

        //***********Text************** */

        scoreText.render();
        healthText.render();
        //******************************* */

        //**********Player and UI********* */
        player.draw();
        //********************************* */
        for(auto& bullet : bullets) {
            bullet.draw();
        }
        for(auto& enemy : enemies) {
            enemy.draw();
        }

        if(!Game::get().paused){
            SDL_RenderPresent(Game::get().getRenderer());
            SDL_Delay(16);
        }
}

void GameScene::doInput(SDL_Event* event){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W]) player.direction.y = -1; // Move up
        if (keystate[SDL_SCANCODE_S]) player.direction.y = 1;  // Move down
        if (keystate[SDL_SCANCODE_A]) player.direction.x = -1; // Move left
        if (keystate[SDL_SCANCODE_D]) player.direction.x = 1;  // Move right

    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEWHEEL:
                exit(0);
                break;
            case SDL_KEYDOWN:
                //keyDown(&event->key);
                if(event->key.keysym.sym == SDLK_ESCAPE){
                    timer.stopTimer();
                    Game::get().paused = true;
                    SceneManager::get().loadSceneAdditive(SceneManager::get().Pause);
                }
                if(event->key.keysym.sym == SDLK_SPACE){
                    player.dodge();
                }
                break;
            default:
                break;
        }
    }
    Uint32 mState = SDL_GetMouseState(NULL, NULL);
    if(mState & SDL_BUTTON(1) ){ //left mouse button held down
        mouseDown = true;
        mouseCounter++;
        return; //can't do charge shot while normal shooting
    }
    else {
        mouseDown = false;
        mouseCounter = -1;
    }
    if(mState & SDL_BUTTON(3)) { //right mouse button held down
        charging = true;
        chargingCounter++;
        SDL_Log("%d", chargingCounter);
    }
    else {
        charging = false;
        chargingCounter = 0;
    }
}

void GameScene::spawnEnemy()
{
    enemies.emplace_back(80, 80, "./../res/spaceship.png");
}