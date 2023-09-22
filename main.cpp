#include "SDL.h"
#include <stdio.h>
#include <sys/time.h>
#include "DisplayManager.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "StaticSprites.hpp"
#include "SpaceShip.hpp"
#include "Color.hpp"
#include "InvisibleWall.hpp"
#include <iostream>
#include <list>

int DEFAULT_COLLISION_VALUE = 0;
Position p1(70, 70);

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

// The way we handle collision is not proper and probably not safe for all framerates. c
void setCollisionRectangle(int collisionMap[], GameObject *go, int id)
{
    // Objet possède une collisionBox?
    CollisionBox *cb = dynamic_cast<CollisionBox *>(go);
    if (cb)
    {
        Position leftTopCorner = go->getPosition();
        for (int x = 0; x < (int)cb->getWidth(); x++)
        {
            collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY())] = id;
            collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY() + cb->getHeight() - 1)] = id;
        }

        for (int y = 0; y < (int)cb->getHeight(); y++)
        {
            collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX(), leftTopCorner.getY() + y)] = id;
            collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + cb->getWidth() - 1, leftTopCorner.getY() + y)] = id;
        }
    }
}

bool checkCollisionAvailability(int collisionMap[], GameObject *go)
{
    // Objet possède une collisionBox?
    CollisionBox *cb = dynamic_cast<CollisionBox *>(go);
    // If a wall collide we will count
    bool rValue = true;
    int collisionPoint = 0;
    if (cb)
    {
        int pointValue;
        Position leftTopCorner = go->getNextPosition();
        if(go->getNextPosition().getX()<0){
            return false;
        }
        if(go->getNextPosition().getY()<0){
            return false;
        }
        if (go->getNextPosition().getX()+cb->getWidth()>WORLD_WIDTH){
            return false;
        }
        if(go->getNextPosition().getY() + cb->getHeight()>WORLD_HEGIHT){
            return false;
        }
        for (int x = 0; x < (int)cb->getWidth(); x++)
        {
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY())];

            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {

                collisionPoint |= TOP;
                cout << "top"<<endl;
                rValue = false;
            }
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY() + cb->getHeight() - 1)];
            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= DOWN;
                cout << "down"<<endl;
                rValue = false;
            }
        }

        for (int y = 0; y < (int)cb->getHeight(); y++)
        {
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX(), leftTopCorner.getY() + y)];

            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= LEFT;
                cout << "left"<<endl;
                rValue = false;
            }
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + cb->getWidth() - 1, leftTopCorner.getY() + y)];
            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= RIGHT;
                cout << "right"<<endl;
                rValue = false;
            }
        }
    }
    (void)collisionPoint;
    return rValue;
}

void printCollisionMap(int collisionMap[], DisplayManager &dm)
{
    for (int x = 0; x < WORLD_WIDTH; x++)
    {
        for (int y = 0; y < WORLD_HEGIHT; y++)
        {
            dm.setPixel(x, y, Color((collisionMap[POSITION_TO_INDEX_WORLD(x, y)] * 50) % 255, (collisionMap[POSITION_TO_INDEX_WORLD(x, y)] * 100) % 255, (collisionMap[POSITION_TO_INDEX_WORLD(x, y)] * 150) % 255));
        }
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    DisplayManager DM;
    StaticSprites background(Position(0, 0), "background.png", DM);
    Player player(p1, DM, 27, 27);
    Position direction(0, 0);
    SpaceShip spaceShip(Position(0, 0), DM, 64, 144);
    InvisibleWall worldBoder(Position(-1, -1), DM, WORLD_WIDTH + 2, WORLD_HEGIHT + 2);
    list<GameObject *> gameObjects = {&background, &player, &spaceShip, &worldBoder};
    int collisionMap[(WORLD_HEGIHT + 2) * (WORLD_WIDTH + 2)];
    DEFAULT_COLLISION_VALUE = background.getId();
    for (int i = 0; i < (WORLD_HEGIHT + 2) * (WORLD_WIDTH + 2); i++)
    {
        collisionMap[i] = DEFAULT_COLLISION_VALUE;
    }
    // filling up collisions map before starting the loop
    for (GameObject *go : gameObjects)
    {
        // Adding to the map the current collision box (they should not overlap in map init, i will did not check that yet)
        setCollisionRectangle(collisionMap, go, go->getId());
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

        // Update every game objet
        for (GameObject *go : gameObjects)
        {
            go->update(deltaTimeInUs);
        }

        // Solve collisions conflicts
        bool conflictsToSolveOnNextIt = true;
        while (conflictsToSolveOnNextIt)
        {
            conflictsToSolveOnNextIt = false;
            for (std::list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
            {
                GameObject *go = *it;
                // nouvelle position (donc mouvement)
                if (!(go->getPosition() == go->getNextPosition()))
                {
                    // place dispo
                    if (checkCollisionAvailability(collisionMap, go))
                    {
                        conflictsToSolveOnNextIt = true;
                        // Remove last rectangle, add new one.
                        setCollisionRectangle(collisionMap, go, DEFAULT_COLLISION_VALUE);
                        go->setPosition(go->getNextPosition());
                        setCollisionRectangle(collisionMap, go, go->getId());
                    }
                }
            }
        }
        // Objects that still haven't done their requested move should be considered as blocked. Reverse their motion.
        for (GameObject *go : gameObjects)
        {
            if (!(go->getPosition() == go->getNextPosition()))
            {
                go->reverseMotion();
            }
        }

        // Render every game object
        for (GameObject *go : gameObjects)
        {
            go->render();
        }
        //printCollisionMap(collisionMap, DM);
        //  Update camera Position and render image.
        DM.setCameraOffset(Position(player.getPosition().getX() - DEFAULT_SCREEN_WIDTH / 2, player.getPosition().getY() - DEFAULT_SCREEN_HEIGHT / 2));
        DM.render();

        // End of frame
        frame++;
        last_frame = current_frame;
    }

    return 0;
}
