#include "Game.h"

//Game Game::instance;

Game::Game(){
    SDL_Log("Game constructor called!");
    this->width = 1500;
    this->height = 1100;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        std::cout << "Could not initialize:" << SDL_GetError() << std::endl;
        std::exit(1);
    }

    //Create window
    gWindow = SDL_CreateWindow( "Overwatch 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        std::cout << "Could not create Window:" << SDL_GetError() << std::endl;
        std::exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    //-1 tells SDL to look for the first graphics accelerating device it can find
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!gRenderer) {
        std::cout << "Could not create Renderer: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))){
        std::cout << "Could not initialize SDL_Image: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    if(TTF_Init() == -1){
        std::cout << "Could not initialize SDL ttf: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    SDL_Log("Initialized everything!");
}

Game::~Game()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Renderer *Game::getRenderer()
{
    return gRenderer;
}
