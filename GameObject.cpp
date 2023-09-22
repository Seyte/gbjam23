#include "GameObject.hpp"
#include <iostream>

int GameObject::_id = 0;

GameObject::GameObject(Position p, DisplayManager &dm) : _position(p), _dm(dm), _myId(_id++), _sprites()
{
}

GameObject::GameObject(Position p, DisplayManager &dm, vector<string> sprites) : _position(p), _dm(dm), _myId(_id++), _sprites(sprites)
{
}

Position GameObject::getPosition()
{
    return _position;
}
void GameObject::setPosition(const Position &p)
{
    _position = p;
}
DisplayManager &GameObject::getDisplayManager()
{
    return _dm;
}
int GameObject::getId()
{
    return _myId;
}
AnimatedSprites &GameObject::getAnimatedSprites()
{
    return _sprites;
}
Position GameObject::getNextPosition()
{
    return _nextPosition;
}
void GameObject::requestMove(Position p)
{
    _nextPosition = p;
}