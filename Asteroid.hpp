#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include "DynamicGameObject.hpp"
#include "CollisionBox.hpp"
#include "utils.hpp"
class Asteroid : public DynamicGameObject, public CollisionBox
{
private:
    // image number, between 1 an 4
    uint _sprite_number;

public:
    Asteroid(Position p, DisplayManager &dm);
    void render();
    void bounce(int direction);
};
#endif