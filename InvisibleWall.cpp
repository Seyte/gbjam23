#include "InvisibleWall.hpp"

InvisibleWall::InvisibleWall(Position p, DisplayManager &dm, uint width, uint height) : GameObject(p, dm), CollisionBox(width, height) {}
void InvisibleWall::update(float deltaTime)
{
    (void)deltaTime;
}
void InvisibleWall::render() {}

void InvisibleWall::bounce(int direction) { (void)direction; }