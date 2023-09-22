#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Position.hpp"
#include "DisplayManager.hpp"
#include "AnimatedSprites.hpp"

class GameObject
{
private:
    Position _position;
    DisplayManager &_dm;
    int _myId;
    static int _id;
    AnimatedSprites _sprites;
    string _sprite;

public:
    GameObject(Position p, DisplayManager &dm);
    GameObject(Position p, DisplayManager &dm, string sprite);
    GameObject(Position p, DisplayManager &dm, vector<string> sprites);
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    void setPosition(const Position &p);
    Position getPosition();
    DisplayManager &getDisplayManager();
    int getId();
};
#endif