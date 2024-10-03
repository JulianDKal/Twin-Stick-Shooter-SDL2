#include "Game.h"

//Game Game::instance;

Game::Game(){
    SDL_Log("Game constructor called!");
    this->width = 1000;
    this->height = 580;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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

    left = 0;
    up = 0;
    down = 0;
    right = 0;

    SDL_Log("Initialized everything!");
}

void Game::Initialize(int width, int height)
{

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

// bool Game::loadMedia()
// {
//     // gHelloWorld = SDL_LoadBMP( "./../res/hello_world.bmp" );
//     // if(!gHelloWorld){
//     //     std::cout << "Unable to load image! " << SDL_GetError() << std::endl;
//     //     return false;
//     // }

//     // //Apply the image
//     // SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

//     // //Update the surface
//     // SDL_UpdateWindowSurface( gWindow ); 

//     // return true;
//     gTexture = IMG_LoadTexture(gRenderer, "./../res/awesomeface.png");
//     if(!gTexture){
//         std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
//         return false;
//     }

//     return true;
// }
