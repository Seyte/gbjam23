#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Position.hpp"
#include "DisplayManager.hpp"

class GameObject
{
private:
    Position _position;
    Position _nextPosition;
    DisplayManager &_dm;
    int _myId;
    static int _id;

public:
    GameObject(Position p, DisplayManager &dm);
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    void setPosition(const Position &p);
    Position getPosition();
    Position getNextPosition();
    void requestMove(Position p);
    virtual void reverseMotion() = 0;
    DisplayManager &getDisplayManager();
    int getId();
};
#endif