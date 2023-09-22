#include "GameObject.hpp"
#include <iostream>

int GameObject::_id = 0;

GameObject::GameObject(Position p, DisplayManager &dm) : _position(p), _dm(dm), _myId(_id++)
{
}

GameObject::GameObject(Position p, DisplayManager &dm, string sprite) : _position(p), _dm(dm), _myId(_id++), _sprite(sprite)
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