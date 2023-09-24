#ifndef SPACESHIPPART_HPP
#define SPACESHIPPART_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "Position.hpp"
#include "Interactable.hpp"

class SpaceShipPart : public Interactable, public CollisionBox
{
public:
    SpaceShipPart(Position p, DisplayManager &dm, vector<string> sprites, uint width, uint height);
    void update(float deltaTime);
    void render();
    void interact(Player &interactor);
    void grab(Player &grabber);
    void reverseMotion();
};

#endif