#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Position.hpp"
#include "DisplayManager.hpp"

class GameObject
{
private:
    Position _position;
    DisplayManager & _dm;

public:
    GameObject(Position p, DisplayManager & dm);
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    void setPosition(const Position &p);
    Position getPosition();
    DisplayManager & getDisplayManager();
};
#endif