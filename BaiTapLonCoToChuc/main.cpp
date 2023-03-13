#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "SDL_func.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Rect m9_rect;
    m9_rect.x = 0;
    m9_rect.y = 0;
    m9_rect.h = 50;
    m9_rect.w = 50;
    initSDL(window, renderer);


     SDL_Rect ex_rect;
     ex_rect.x = 0;
     ex_rect.y = 70;
     ex_rect.h = 50;
     ex_rect.w = 50;
     int cex = 0;


    SDL_Texture* background = loadtexture("background.png", renderer);
    SDL_Texture* m9 = loadtexture("m9.png", renderer);
    SDL_Texture* ex = loadtexture("Excalibur.png", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, m9, NULL, &m9_rect);

    int i = 5;

    bool x = 1;
    while (x)
    {
        x = dieuhuong(m9_rect);

        ex_rect.x = ex_rect.x + i;


        if (ex_rect.x >= SCREEN_WIDTH)
        {
            cex = 1;
            ex_rect.x = 0;

        }
        if (cex)
        {
            ex_rect.y = rand() % 350;
            cex = 0;
            i++;
        }
        if (m9_rect.x + m9_rect.w >= ex_rect.x &&
            ex_rect.x + ex_rect.w >= m9_rect.x &&
            m9_rect.y + m9_rect.h >= ex_rect.y &&
            ex_rect.y + ex_rect.h >= m9_rect.y)
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_RenderPresent(renderer);
            break;
        }

        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, ex, NULL, &ex_rect);
        SDL_RenderCopy(renderer, m9, NULL, &m9_rect);
        SDL_RenderPresent(renderer);
    }


    SDL_Delay(1000);
    waitUntilKeyPressed();
    HuyTexture(background);
    HuyTexture(m9);
    HuyTexture(ex);
    quitSDL(window, renderer);
    return 0;


}
