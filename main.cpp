#include "SDL.h"
#include <stdio.h>
#include <sys/time.h>
#include "DisplayManager.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "StaticSprites.hpp"
#include "SpaceShip.hpp"
#include <iostream>
#include <list>

Position p1(50, 50);

bool running = true;

struct timeval game_start_timer;
struct timeval game_stop_timer;

struct timeval last_frame;
struct timeval current_frame;
int deltaTime;
float deltaTimeInUs;

int frame = 0;
void getInput(Position &p)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        int x = 0;
        int y = 0;
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
        p.setX(x);
        p.setY(y);
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    vector<string> playerSprites = {"rocketman_0.png", "rocketman_1.png", "rocketman_2.png"};

    DisplayManager DM;
    Player player(p1, DM, 27, 27, playerSprites);
    Position direction(0, 0);
    StaticSprites background(Position(0, 0), "background.png", DM);
    SpaceShip spaceShip(Position(0, 0), DM, 64, 144);
    list<GameObject *> gameObjects = {&background, &player, &spaceShip};
    int collisionMap[DEFAULT_SCREEN_PIXEL_COUNT];
    for (int i = 0; i < DEFAULT_SCREEN_PIXEL_COUNT; i++)
    {
        collisionMap[i] = 0;
    }
    // filling up collisions map before starting the loop
    for (GameObject *go : gameObjects)
    {
        // Objet possède une collisionBox?
        CollisionBox *cb = dynamic_cast<CollisionBox *>(go);
        if (cb)
        {
            Position leftTopCorner = go->getPosition();
            int id = go->getId();
            // Adding to the map the current collision box (they should not overlap in map init, i will did not check that yet)
            for (int x = 0; x < (int)cb->getWidth(); x++)
            {
                collisionMap[POSITION_TO_INDEX(leftTopCorner.getX() + x, leftTopCorner.getY())] = id;
                collisionMap[POSITION_TO_INDEX(leftTopCorner.getX() + x, leftTopCorner.getY() + cb->getHeight() - 1)] = id;
            }

            for (int y = 0; y < (int)cb->getHeight(); y++)
            {
                collisionMap[POSITION_TO_INDEX(leftTopCorner.getX(), leftTopCorner.getY() + y)] = id;
                collisionMap[POSITION_TO_INDEX(leftTopCorner.getX() + cb->getWidth() - 1, leftTopCorner.getY() + y)] = id;
            }
        }
    }

    gettimeofday(&game_start_timer, NULL);
    while (running)
    {
        // calculate deltaTime
        gettimeofday(&current_frame, NULL);
        deltaTime = (current_frame.tv_sec * 1000000 + current_frame.tv_usec) - (last_frame.tv_sec * 1000000 + last_frame.tv_usec);
        deltaTimeInUs = (float)deltaTime / (float)1000000;
        // Get Inputs
        getInput(direction);
        player.setDirection(direction);

        // Update and render every game objet
        for (GameObject *go : gameObjects)
        {
            go->update(deltaTimeInUs);
            go->render();
        }

        // Update camera Position and render image.
        DM.setCameraOffset(Position(player.getPosition().getX() - DEFAULT_SCREEN_WIDTH / 2, player.getPosition().getY() - DEFAULT_SCREEN_HEIGHT / 2));
        DM.render();

        // End of frame
        frame++;
        last_frame = current_frame;
    }

    return 0;
}
