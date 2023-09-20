#include "GameObject.hpp"

GameObject::GameObject(Position p, DisplayManager& dm) : _position(p), _dm(dm) {}

Position GameObject::getPosition()
{
    return _position;
}
void GameObject::setPosition(const Position &p)
{
    _position = p;
}
DisplayManager& GameObject::getDisplayManager(){
    return _dm;
}