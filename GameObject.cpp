#include "GameObject.hpp"

GameObject::GameObject(Position p) : _position(p) {}

Position GameObject::getPosition()
{
    return _position;
}
void GameObject::setPosition(const Position &p)
{
    _position = p;
}