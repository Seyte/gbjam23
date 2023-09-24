#ifndef INVISIBLE_WALL_HPP
#define INVISIBLE_WALL_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"

class InvisibleWall : public GameObject, public CollisionBox
{
public:
    InvisibleWall(Position p, DisplayManager &dm, uint width, uint height);
    void update(float deltaTime);
    void render();
    void bounce(int direction);
};

#endif