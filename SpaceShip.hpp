#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "utils.hpp"
#include "Interactable.hpp"
#include <algorithm>

class SpaceShip : public Interactable, public CollisionBox
{
private:
    int _fixablePartID;
    bool fixed = false;

public:
    SpaceShip(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites, int distance, int fixablePartID);
    void update(float deltaTime);
    void render();
    void bounce(int direction);
    void interact(Player &interactor);
    void grab(Player &grabber);
};

#endif