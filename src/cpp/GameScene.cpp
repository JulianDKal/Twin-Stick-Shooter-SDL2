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
    charge = 0;
    for(auto& enemy : enemies){
        enemy.active = false;
    }
    timer.stopTimer();
    SDL_RenderSetViewport(Game::get().getRenderer(), NULL);
}

void GameScene::UpdateGame()
{
        doInput(event);
        if(mouseDown && !(mouseCounter % 10)) bullets.emplace_back(player.getPosX(), player.getPosY());
        player.move();

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
                    charge += 10;
                }
            }
        }

        for(auto& bullet : bullets) {
            bullet.updatePositon();
        }
        for(auto& enemy : enemies) {
            enemy.updatePosition(player.getPosX(), player.getPosY());
            if(player.isDodging) continue; //player can't get hurt when dodging
            else if(calculateDistance(enemy.getPosX(), enemy.getPosY(), player.getPosX(), player.getPosY()) <= 20)
            {
                enemy.active = false;
                Game::get().playerHealth -= 2;
                return;
            }
        }
        if(Game::get().playerHealth <= 0) SceneManager::get().loadScene(SceneManager::get().GameOver);
        if(charge >= 100) charge = 100;
        chargeRect.w = charge * 1.5f;
}

void GameScene::RenderGame()
{
        //Actual Drawing happens here
        SDL_RenderClear(Game::get().getRenderer());
        SDL_RenderSetViewport(Game::get().getRenderer(), &render_viewport);
        //std::cout << render_viewport.x << " " << render_viewport.y << std::endl;
        SDL_RenderCopy(Game::get().getRenderer(), background, NULL, NULL);

        //***********Text************** */
        scoreText.render();
        healthText.render();
        //******************************* */

        //**********Player and UI********* */
        SDL_SetRenderDrawColor(Game::get().getRenderer(), 255, 50, 50, 255);
        SDL_RenderFillRect(Game::get().getRenderer(), &chargeRect); //draw charge bar
        player.draw();
        //********************************* */
        for(auto& bullet : bullets) {
            bullet.draw();
        }
        for(auto& enemy : enemies) {
            enemy.draw();
        }

        SDL_SetRenderDrawColor(Game::get().getRenderer(), 0, 0, 0, 255); //reset background to black

        if(!Game::get().paused){
            SDL_RenderPresent(Game::get().getRenderer());
            SDL_Delay(16); //62 FPS
        }

}

void GameScene::doInput(SDL_Event* event){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W]) {
            player.direction.y = -1;
            render_viewport.y += 2;
        } // Move up
        if (keystate[SDL_SCANCODE_S]) {
            player.direction.y = 1;
            render_viewport.y -= 2;
        }  // Move down
        if (keystate[SDL_SCANCODE_A]) {
            player.direction.x = -1;
            render_viewport.x += 2;
        } // Move left
        if (keystate[SDL_SCANCODE_D]) {
            player.direction.x = 1;
            render_viewport.x -= 2;
        }  // Move right

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
        charge--;
        if(charge <= 0) charge = 0;
        SDL_Log("%d", charge);
    }
    else {
        charging = false;
    }
}

void GameScene::spawnEnemy()
{
    enemies.emplace_back(80, 80, "./../res/ghost_pixel.png");
}
