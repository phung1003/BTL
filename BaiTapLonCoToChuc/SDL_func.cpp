#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_func.hpp"
using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}



SDL_Texture* loadtexture( string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTex = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) cout << "Unable to load image" << SDL_GetError;
    else
    {
        newTex = SDL_CreateTextureFromSurface( renderer, loadedSurface);
        if (newTex == nullptr)
           cout << "Unable to create texture ";
        SDL_FreeSurface(loadedSurface);
    }
    return newTex;
}



bool dieuhuong(SDL_Rect &filled_rect)
{
    SDL_Event e;


    while ( SDL_PollEvent(&e) != 0) {
    switch (e.key.keysym.sym)
    {
       case SDLK_LEFT:
           if (filled_rect.x != 0) filled_rect.x = filled_rect.x - 15;
           break;
       case SDLK_RIGHT:
           if (filled_rect.x + 50 != SCREEN_WIDTH) filled_rect.x = filled_rect.x + 15;
           break;
       case SDLK_UP:
           if (filled_rect.y != 0) filled_rect.y = filled_rect.y - 15;
           break;
       case SDLK_DOWN:
           if (filled_rect.y + 50 != SCREEN_HEIGHT) filled_rect.y = filled_rect.y + 15;
           break;
       case SDLK_ESCAPE:
           return 0;
           break;
    }
    }
    return 1;
}


void HuyTexture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}



SDL_Rect Excalibur(){

    SDL_Rect ex_rect;
    ex_rect.h = 50;
    ex_rect.w = 50;
    return ex_rect;

}

void AutoMove(SDL_Rect &rect)
{
    rect.x = rect.x + 10;
}





