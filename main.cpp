#include "SDL.h"
#include <stdio.h>
#include "DisplayManager.hpp"
    int x = 50;
    int y = 50;
void doInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                y--;
                break;
            case SDLK_DOWN:
                y++;
                break;
            case SDLK_LEFT:
                x--;
                break;
            case SDLK_RIGHT:
                x++;
                break;
            }
            break;
        case SDL_QUIT:
            exit(0);
            break;

        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    DisplayManager DM;
    Color c;
    c._r = 255;
    c._g = 0;
    c._b = 0;
    while (1)
    {
        if (x>0 && y > 0){
            DM.setPixel((uint)x,(uint)y,c);
        }
        DM.render();
        doInput();
    }

    exit(0);
}
