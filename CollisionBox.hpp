#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP
#include "utils.hpp"
class CollisionBox
{
private:
    uint _width;
    uint _height;

public:
    CollisionBox(uint width, uint height);
    uint getWidth();
    uint getHeight();
};

#endif