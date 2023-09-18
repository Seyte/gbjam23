#include "SDL.h"
#include <stdio.h>
#include <sys/time.h>
#include "DisplayManager.hpp"

//TODO: delete these variables, only here for print test
int x = 50;
int y = 50;

struct timeval game_start_timer;
struct timeval game_stop_timer;

int frame = 0;
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
            gettimeofday (&game_stop_timer, NULL);
            printf("We had %d frames rendered in %ld seconds. This is approximatly %f fps\n",frame,game_stop_timer.tv_sec - game_start_timer.tv_sec, (float)(frame)/(float)(game_stop_timer.tv_sec - game_start_timer.tv_sec));
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
    gettimeofday (&game_start_timer, NULL);
    while (1)
    {
        if (x > 0 && y > 0)
        {
            DM.setPixel((uint)x, (uint)y, c);
        }
        DM.render();
        doInput();
        frame++;
    }

    exit(0);
}
