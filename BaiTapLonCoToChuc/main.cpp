#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "SDL_func.hpp"

using namespace std;

SDL_Renderer* renderer;
SDL_Window* window;

int movex , movey = 0;


int main(int argc, char* argv[])
{
    srand(time(0));
    initSDL(window, renderer);
    SDL_Texture* background = loadtexture("background.png", renderer);
    SDL_Texture* m9 = loadtexture("m9.png", renderer);
    SDL_Texture* ex = loadtexture("Excalibur.png", renderer);
    SDL_Texture* laser = loadtexture("laser.png", renderer);
    SDL_Texture* ball1 = loadtexture("ball1.png", renderer);
    SDL_Texture* ball2 = loadtexture("ball2.png", renderer);
    SDL_Texture* ball3 = loadtexture("ball3.png", renderer);
    SDL_Texture* ghost = loadtexture("Excalibur.png", renderer);




    SDL_Rect m9_rect;
    m9_rect.x = 0;
    m9_rect.y = 0;
    m9_rect.h = 50;
    m9_rect.w = 50;



    SDL_Rect ex_rect;
    ex_rect.x = 0;
    ex_rect.y = rand() % (SCREEN_HEIGHT - 50);
    ex_rect.h = 50;
    ex_rect.w = 50;
    int cex = 0;


    SDL_Rect laser_rect;
    laser_rect.x = SCREEN_WIDTH - 50;
    laser_rect.y = rand() % (SCREEN_HEIGHT - 50);
    laser_rect.h = 50;
    laser_rect.w = 50;
    int claser = 0;



    SDL_Rect ball_rect;
    ball_rect.x = SCREEN_WIDTH;
    ball_rect.y = SCREEN_HEIGHT;
    ball_rect.h = 50;
    ball_rect.w = 50;
    int cball = 0;
    float aball = 1;
    int bball = 0;


    //ball_rect.y = a*ball_rect.y + b;


    SDL_Rect ghost_rect;
    ghost_rect.x = SCREEN_WIDTH;
    ghost_rect.y = 0;
    ghost_rect.h = 50;
    ghost_rect.w = 50;
    float aghost = 1;
    int bghost = 0;
    int cghost = 0;



    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, m9, NULL, &m9_rect);

    float i = 5;
    int li = 15;
    int bi = 1;
    bool x = 1;
    bool m = 1;

        while (x)
    {



        SDL_RenderCopy(renderer, background, NULL, NULL);

        if (bi == 1)
        {
            SDL_RenderCopy(renderer, ball1, NULL, &ball_rect);
            bi++;
        }
        else if (bi == 2)
        {
            SDL_RenderCopy(renderer, ball2, NULL, &ball_rect);
            bi++;
        }
        else
        {
            SDL_RenderCopy(renderer, ball3, NULL, &ball_rect);
            bi = 1;
        }







        // excalibur
        if (ex_rect.x >= SCREEN_WIDTH)
        {
            cex = 1;
            ex_rect.x = 0;


            ex_rect.y = rand() % (SCREEN_HEIGHT - 50);
            cex = 0;
            i = i+0.05;
        }


        // laser beam
        if (laser_rect.w >= SCREEN_WIDTH + 50)
        {
            claser = 1;
            laser_rect.w = 50;
            laser_rect.x = SCREEN_WIDTH;

            laser_rect.y = rand() % (SCREEN_HEIGHT - laser_rect.h);
            claser = 0;

        }




        //Ball
        if (ball_rect.x <0 || ball_rect.y >= SCREEN_HEIGHT || ball_rect.x > SCREEN_WIDTH || ball_rect.y < 0 )
        {
            ball_rect.x = rand() % (SCREEN_WIDTH - 50);
            if (ball_rect.x > SCREEN_WIDTH/2)
            {
                cball = 0;
            }
            else
            {
                cball = 1;
            }
            ball_rect.y = 0;


            bball = ball_rect.x;

            aball = 1.0*(m9_rect.x - bball)/ (m9_rect.y + 200);
            if (aball > 1) aball = 1;
            if (aball < -1) aball = -1;

        }





        //Dead ex
        if (m9_rect.x + m9_rect.w >= ex_rect.x &&
            ex_rect.x + ex_rect.w >= m9_rect.x &&
            m9_rect.y + m9_rect.h >= ex_rect.y &&
            ex_rect.y + ex_rect.h >= m9_rect.y)
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_Delay(1000);
            SDL_RenderPresent(renderer);
            break;
        }


        //Dead laser
        if (m9_rect.x + m9_rect.w >= laser_rect.x &&
            laser_rect.x + laser_rect.w >= m9_rect.x &&
            m9_rect.y  + m9_rect.h >= laser_rect.y &&
            laser_rect.y + laser_rect.h >= m9_rect.y )
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_Delay(1000);
            SDL_RenderPresent(renderer);

            break;
        }


        //Dead ex
        if (m9_rect.x + m9_rect.w >= ex_rect.x &&
            ex_rect.x + ex_rect.w >= m9_rect.x &&
            m9_rect.y + m9_rect.h >= ex_rect.y &&
            ex_rect.y + ex_rect.h >= m9_rect.y )
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_Delay(1000);
            SDL_RenderPresent(renderer);

            break;
        }


        //Dead ball
        if (m9_rect.x + m9_rect.w >= ball_rect.x &&
            ball_rect.x + ball_rect.w >= m9_rect.x  &&
            m9_rect.y + m9_rect.h >= ball_rect.y &&
            ball_rect.y + ball_rect.h >= m9_rect.y )
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_Delay(1000);
            SDL_RenderPresent(renderer);

            break;
        }



        if (m9_rect.x + m9_rect.w >= ghost_rect.x &&
            ghost_rect.x + ghost_rect.w >= m9_rect.x &&
            m9_rect.y + m9_rect.h >= ghost_rect.y &&
            ghost_rect.y + ghost_rect.h >= m9_rect.y)
        {
            SDL_Texture* endg = loadtexture("endgame.png", renderer);
            SDL_RenderCopy(renderer, endg, NULL, NULL);
            SDL_Delay(1000);
            SDL_RenderPresent(renderer);
            break;
        }



        SDL_RenderCopy(renderer, ghost, NULL, &ghost_rect);
        SDL_RenderCopy(renderer, ex, NULL, &ex_rect);
        SDL_RenderCopy(renderer, m9, NULL, &m9_rect);
        SDL_RenderCopy(renderer, laser, NULL, &laser_rect);
        SDL_RenderPresent(renderer);



        x = dieuhuong(m9_rect, movex, movey);
        if (m9_rect.x + movex < SCREEN_WIDTH && m9_rect.x + movex >= 0) m9_rect.x = m9_rect.x + movex;
        if (m9_rect.y + movey < SCREEN_HEIGHT && m9_rect.y + movey >= 0) m9_rect.y = m9_rect.y + movey;


        if (ghost_rect.x > m9_rect.x) ghost_rect.x = ghost_rect.x - 3;
        else if (ghost_rect.x < m9_rect.x) ghost_rect.x = ghost_rect.x + 3;
        if (ghost_rect.y > m9_rect.y) ghost_rect.y = ghost_rect.y - 3;
        else if (ghost_rect.y < m9_rect.y) ghost_rect.y = ghost_rect.y + 3;



        cghost++;
        if (cghost == 300)
        {
            ghost_rect.x = SCREEN_WIDTH;
            ghost_rect.y = rand() % (SCREEN_HEIGHT - ghost_rect.h);
            cghost = 0;

        }


        ex_rect.x = ex_rect.x + i;


        laser_rect.w = laser_rect.w + li;
        laser_rect.x = round(laser_rect.x  - li);


        ball_rect.y = ball_rect.y + i;
        ball_rect.x = aball*ball_rect.y + bball;


    }


    SDL_Delay(1000);
    waitUntilKeyPressed();
    HuyTexture(background);
    HuyTexture(m9);
    HuyTexture(ex);
    quitSDL(window, renderer);
    return 0;


}
