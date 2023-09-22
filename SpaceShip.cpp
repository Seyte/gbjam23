#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Position p, DisplayManager &dm, uint width, uint height) : GameObject(p, dm), CollisionBox(width, height) {}

void SpaceShip::update(float deltaTime) {
    (void) deltaTime;
}

void SpaceShip::render()
{

    getDisplayManager().setTexture("ship_nose_fixed.png", (uint)getPosition().getX(), (uint)getPosition().getY());
}

void SpaceShip::reverseMotion(){}