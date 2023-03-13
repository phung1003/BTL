#ifndef SDl_func

#define SDL_func

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

bool dieuhuong(SDL_Rect &filled_rect);

SDL_Texture* loadtexture( string path, SDL_Renderer* renderer);

void HuyTexture(SDL_Texture* texture);

SDL_Rect Excalibur();

void AutoMove(SDL_Rect &rect);

#endif // SDl_func
