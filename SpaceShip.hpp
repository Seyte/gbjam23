#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "utils.hpp"

class SpaceShip : public GameObject, public CollisionBox
{
private:
public:
    SpaceShip(Position p, DisplayManager &dm, uint width, uint height);
    void update(float deltaTime);
    void render();
};

#endif