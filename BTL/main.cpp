#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();


SDL_Texture* loadtexture( string, SDL_Renderer*);

SDL_Rect spawn()
{
    SDL_Rect rect;
    rect.x=0;
    rect.y =10;
    rect.w = 100;
    rect.h = 100;
    return rect;
}
void rectmove(SDL_Rect rect)
{
    rect.w = rect.w + 30;
}

bool dieuhuong(SDL_Rect &filled_rect)
{
    SDL_Event e;
    if (SDL_WaitEvent(&e) != 0)
    {
    switch (e.key.keysym.sym)
    {
       case SDLK_LEFT:
           filled_rect.x = filled_rect.x - 5;
           break;
       case SDLK_RIGHT:
           filled_rect.x = filled_rect.x + 5;
           break;
       case SDLK_UP:
           filled_rect.y = filled_rect.y - 5;
           break;
       case SDLK_DOWN:
           filled_rect.y = filled_rect.y + 5;
           break;
       case SDLK_ESCAPE:
           return 0;
           break;
    }
    }
    return 1;
}




int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);




     SDL_Texture* background = loadtexture("1280px-Auto_Racing_Yellow.svg.png", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_Texture* ransha = loadtexture("80-806587_post-lewd-anime-girl-sign.png", renderer);
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 900;

    SDL_QueryTexture(background,NULL,NULL, &rect.w, &rect.h);
    rect.w /= 2;
    rect.h /= 2;
    SDL_RenderCopy(renderer, ransha, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_Rect srect;
    srect.h = 100;
   srect.y =100;
    srect.w = 100;
    srect.x=100;



    bool x = 1;
    while (x)
    {

        x = dieuhuong(rect); SDL_RenderCopy(renderer, background, NULL, NULL);
       SDL_RenderCopy(renderer, ransha, NULL, &rect);
     //   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green


  //  SDL_RenderFillRect(renderer, &srect);
    SDL_RenderPresent(renderer);
    //srect.x = srect.x+10;

    }






    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}


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




