#include "SDL2/SDL.h"
#include <stdio.h>
#include <sys/time.h>
#include "DisplayManager.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "StaticSprites.hpp"
#include "SpaceShip.hpp"
#include "Color.hpp"
#include "InvisibleWall.hpp"
#include "Interactable.hpp"
#include "SpaceShipPart.hpp"
#include <iostream>
#include <list>

#define INTERACTION_DIST 10

int DEFAULT_COLLISION_VALUE = 0;
Position p1(70, 70);
vector<Interactable *> interactableObjects;

bool running = true;
bool first = true;

struct timeval game_start_timer;
struct timeval game_stop_timer;

struct timeval last_frame;
struct timeval current_frame;
int deltaTime;
float deltaTimeInUs;

int frame = 0;

void interactWithObjects(Player &player)
{
    for (Interactable *interactable : interactableObjects)
    {
        cout << "id: " << interactable->getId() << "| dist: " << player.getPosition().dist(interactable->getPosition()) << "\n";
        if (player.getPosition().dist(interactable->getPosition()) <= INTERACTION_DIST)
        {
            interactable->interact(player);
        }
    }
}

void getInput(Position &p, Player &player)
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
            case SDLK_a:
                cout << "pressed a\n";
                interactWithObjects(player);
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

int checkCollisionAvailability(int collisionMap[], GameObject *go)
{
    // Objet possède une collisionBox?
    CollisionBox *cb = dynamic_cast<CollisionBox *>(go);
    // If a wall collide we will count
    int collisionPoint = 0;
    if (cb)
    {
        int pointValue;
        Position leftTopCorner = go->getNextPosition();
        if (go->getNextPosition().getX() < 0)
        {
            collisionPoint |= LEFT;
        }
        if (go->getNextPosition().getY() < 0)
        {
            collisionPoint |= TOP;
        }
        if (go->getNextPosition().getX() + cb->getWidth() > WORLD_WIDTH)
        {
            collisionPoint |= RIGHT;
        }
        if (go->getNextPosition().getY() + cb->getHeight() > WORLD_HEGIHT)
        {
            collisionPoint |= DOWN;
        }
        if (collisionPoint != 0)
        {
            return collisionPoint;
        }
        for (int x = 0; x < (int)cb->getWidth(); x++)
        {
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY())];

            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {

                collisionPoint |= TOP;
            }
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + x, leftTopCorner.getY() + cb->getHeight() - 1)];
            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= DOWN;
            }
        }

        for (int y = 0; y < (int)cb->getHeight(); y++)
        {
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX(), leftTopCorner.getY() + y)];

            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= LEFT;
            }
            pointValue = collisionMap[POSITION_TO_INDEX_WORLD(leftTopCorner.getX() + cb->getWidth() - 1, leftTopCorner.getY() + y)];
            if (!(pointValue == go->getId() || pointValue == DEFAULT_COLLISION_VALUE))
            {
                collisionPoint |= RIGHT;
            }
        }
    }
    return collisionPoint;
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

    vector<string> playerSprites = {"rocketman_0.png", "rocketman_1.png", "rocketman_2.png"};

    DisplayManager DM;
    StaticSprites background(Position(0, 0), "map_tiled.png", DM);
    Player player(p1, DM, 18, 18, playerSprites);
    Position direction(0, 0);
    SpaceShip spaceShip(Position(0, 0), DM, 64, 144);
    SpaceShipPart firstPart(Position(100, 30), DM, vector<string>{"spaceshippart_1.png"}, 18, 18);
    InvisibleWall worldBoder(Position(-1, -1), DM, WORLD_WIDTH + 2, WORLD_HEGIHT + 2);
    list<GameObject *> gameObjects = {&background, &player, &spaceShip, &worldBoder, &firstPart};
    interactableObjects.push_back(&firstPart);
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
        getInput(direction, player);
        player.setDirection(direction);

        // Update and render every game objet
        if (!first)
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
                    if (checkCollisionAvailability(collisionMap, go) == 0)
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
                int side = checkCollisionAvailability(collisionMap, go);
                go->bounce(side);
            }
        }

        // Render every game object
        for (GameObject *go : gameObjects)
        {
            go->render();
        }
        // printCollisionMap(collisionMap, DM);
        // Update camera Position and render image.
        DM.setCameraOffset(Position(player.getPosition().getX() - DEFAULT_SCREEN_WIDTH / 2, player.getPosition().getY() - DEFAULT_SCREEN_HEIGHT / 2));
        DM.render();

        // End of frame
        frame++;
        last_frame = current_frame;
        first = false;
    }

    return 0;
}
