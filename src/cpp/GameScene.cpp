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
    
    player = Player(Game::get().width / 2, Game::get().height/2, 70, 70, "./../res/spaceship.png");
    Camera::get().setPos(player.getPosX(), player.getPosY());
    SDL_Texture* backgound = loadTexture("./../res/background.jpg");
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
    // TODO: Refactor this 
    enemies.clear();
    bullets.clear();
}

void GameScene::UpdateGame()
{
        static Uint32 lastSpawnTimeGhost = 0, bigGhostTime = 0;
        Uint32 currentTime = SDL_GetTicks();
        //spawns small ghosts
        if(currentTime - lastSpawnTimeGhost >= 2000){
            enemies.emplace_back(std::make_unique<Ghost>(80, 80, "./../res/spaceship.png"));
            lastSpawnTimeGhost = currentTime;
        }
        //spawns big ghosts
        if(currentTime - bigGhostTime >= 5000){
            enemies.emplace_back(std::make_unique<BigGhost>(100, 100, "./../res/spaceship.png"));
            bigGhostTime = currentTime;
        }

        doInput(event);
        player.move();

        scoreText.update("Score: " + std::to_string(Game::get().score));
        healthText.update("Health: " + std::to_string(Game::get().playerHealth));

        bullets.remove_if(isInactive);
        enemies.remove_if([](const std::unique_ptr<Enemy>& enemy) {
        return !enemy->active; // Access active member via unique_ptr
    });

        //Check for bullet and enemy collision
        for(auto& bullet : bullets) {
            for(auto& enemy : enemies) {
                if(calculateDistance(bullet.getPosX(), bullet.getPosY(), enemy->getPosX(), enemy->getPosY()) <= 35){
                    enemy->takeDamage(1);
                    bullet.active = false;
                    charge += 10;
                }
            }
        }

        for(auto& bullet : bullets) {
            bullet.updatePositon();
        }
        for(auto& enemy : enemies) {
            enemy->updatePosition(player.getPosX(), player.getPosY());
            if(player.isDodging) continue; //player can't get hurt when dodging
            else if(calculateDistance(enemy->getPosX(), enemy->getPosY(), player.getPosX(), player.getPosY()) <= 20)
            {
                enemy->active = false;
                Game::get().playerHealth -= 2;
                return;
            }
        }
        if(Game::get().playerHealth <= 0) SceneManager::get().loadScene(SceneManager::get().GameOver);
        if(charge >= 100) charge = 100;
        chargeRect.w = charge * 1.5f;

        Camera::get().setPos(player.getPosX() - Game::get().width / 2, player.getPosY() - Game::get().height / 2);
}

void GameScene::RenderGame()
{
        //Actual Drawing happens here
        SDL_RenderClear(Game::get().getRenderer());
        drawEntity(background, 0, 0);

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
            enemy->draw();
        }

        SDL_SetRenderDrawColor(Game::get().getRenderer(), 0, 0, 0, 255); //reset background to black

        if(!Game::get().paused){
            SDL_RenderPresent(Game::get().getRenderer());
            SDL_Delay(16); //62 FPS
        }

}

void GameScene::doInput(SDL_Event* event){
    Uint32 currentTime = SDL_GetTicks();

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W]) {
            player.direction.y = -1;
        } // Move up
        if (keystate[SDL_SCANCODE_S]) {
            player.direction.y = 1;
        }  // Move down
        if (keystate[SDL_SCANCODE_A]) {
            player.direction.x = -1;
        } // Move left
        if (keystate[SDL_SCANCODE_D]) {
            player.direction.x = 1;
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
                if(event->key.keysym.sym == SDLK_ESCAPE){
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
        //shoot if time elapsed since last shot is big enough
        if(currentTime - lastShotTime >= 220){
            bullets.emplace_back(player.getPosX(), player.getPosY());
            lastShotTime = SDL_GetTicks();
        }
        return; //can't do charge shot while normal shooting
    }
    if(mState & SDL_BUTTON(3)) { //right mouse button held down
        charging = true;
        charge--;
        if(charge <= 0) charge = 0;
    }
    else {
        charging = false;
    }
}
