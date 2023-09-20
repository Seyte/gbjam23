#include "SDL.h"
#include <stdio.h>
#include <sys/time.h>
#include "DisplayManager.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "StaticSprites.hpp"

Position p1(50, 50);

bool running = true;

struct timeval game_start_timer;
struct timeval game_stop_timer;

struct timeval last_frame;
struct timeval current_frame;
int deltaTime;
float deltaTimeInUs;

int frame = 0;
Position getInput(void)
{
    SDL_Event event;

    int x = 0;
    int y = 0;
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
            default:
                break;
            }
            break;
        case SDL_QUIT:
            gettimeofday(&game_stop_timer, NULL);
            printf("We had %d frames rendered in %ld seconds. This is approximatly %f fps\n", frame, game_stop_timer.tv_sec - game_start_timer.tv_sec, (float)(frame) / (float)(game_stop_timer.tv_sec - game_start_timer.tv_sec));
            running = false;
            break;

        default:
            break;
        }
    }
    return Position(x, y);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    DisplayManager DM;
    Player player(p1, DM);
    StaticSprites background(Position(0,0), "background.png",DM);
    Color c;
    c._r = 255;
    c._g = 0;
    c._b = 0;
    gettimeofday(&game_start_timer, NULL);
    while (running)
    {
        gettimeofday(&current_frame, NULL);
        deltaTime = (current_frame.tv_sec * 1000000 + current_frame.tv_usec) - (last_frame.tv_sec * 1000000 + last_frame.tv_usec);
        deltaTimeInUs = (float)deltaTime / (float)1000000;
        background.render();
        DM.setPixel((uint)player.getPosition().getX(), (uint)player.getPosition().getY(), c);
        DM.render();
        Position pos = getInput();
        player.setDirection(pos);
        player.update(deltaTimeInUs);
        frame++;
        last_frame = current_frame;
    }

    return 0;
}
