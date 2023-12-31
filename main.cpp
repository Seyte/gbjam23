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
#include "Interactable.hpp"
#include "SpaceShipPart.hpp"
#include "Asteroid.hpp"
#include "StaticText.hpp"
#include <iostream>
#include <list>

#define INTERACTION_DIST 10

int DEFAULT_COLLISION_VALUE = 0;
Position p1(130, 70);
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
bool ended = false;

void interactWithObjects(Player &player)
{
    Position p(player.getPosition().getX() + (player.getWidth() / 2), player.getPosition().getY() + (player.getHeight() / 2));
    for (Interactable *interactable : interactableObjects)
    {
        if (getDistance(p, interactable->getInteractionPoint()) <= interactable->interactionDistance)
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
            if (!ended)
            {
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
                    interactWithObjects(player);
                    break;
                default:
                    break;
                }
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

    vector<string> playerSprites = {"spacedude_0.png", "spacedude_1.png", "spacedude_2.png", "spacedude_3.png", "spacedude_4.png", "spacedude_5.png"};

    DisplayManager DM;
    StaticSprites background1(Position(0, 0), "map_tiled.png", DM);
    Player player(p1, DM, 18, 18, playerSprites);
    Position direction(0, 0);
    SpaceShipPart firstPart(Position(400, 30), DM, vector<string>{"spaceshippart_1.png"}, 23, 18, 18);
    SpaceShip spaceShip(Position(0, 0), DM, 96, 144, vector<string>{"rocket_broken_deadheart.png", "rocket_broken_glowingheart.png"}, "rocket_fixed.png", 15, firstPart.getId(), Position(0 + 96, 0 + 114));
    SpaceShipPart secondPart(Position(359, 230), DM, vector<string>{"spaceshippart_1.png"}, 23, 18, 18);
    SpaceShip spaceShipMiddle(Position(0, 144), DM, 96, 144, vector<string>{"rocket_middle_broken_deadheart.png", "rocket_middle_broken_glowingheart.png"}, "rocket_middle_fixed.png", 15, secondPart.getId(), Position(0 + 96, 144 + 72));
    InvisibleWall worldBoder(Position(-1, -1), DM, WORLD_WIDTH + 2, WORLD_HEGIHT + 2);
    Asteroid asteroid(Position(150, 80), DM);
    asteroid.setDirection(Position(7, 2));
    // StaticText inventoryText("Parts: ", 12, Position(130, 0), 20, 10, true, DM);
    list<GameObject *> gameObjects = {&background1, &player, &spaceShip, &worldBoder, &firstPart, &asteroid, &secondPart, &spaceShipMiddle};
    interactableObjects.push_back(&firstPart);
    interactableObjects.push_back(&spaceShip);
    interactableObjects.push_back(&secondPart);
    interactableObjects.push_back(&spaceShipMiddle);
    int collisionMap[(WORLD_HEGIHT + 2) * (WORLD_WIDTH + 2)];
    DEFAULT_COLLISION_VALUE = background1.getId();
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

        if (ended)
        {
            StaticText inventoryText("You Win!", 32, Position(25, 40), 100, 50, true, DM);
            inventoryText.render();
            DM.render();
            getInput(direction, player);
            continue;
        }
        // check win
        if (spaceShip.isFixed() && spaceShipMiddle.isFixed())
        {
            ended = true;
            continue;
        }

        // Get Inputs
        getInput(direction, player);
        // Check for grabs
        for (Interactable *interactable : interactableObjects)
        {
            if (interactable->grabbed)
            {
                setCollisionRectangle(collisionMap, interactable, DEFAULT_COLLISION_VALUE);
            }
        }
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
