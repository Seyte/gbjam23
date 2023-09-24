#include "SpaceShipPart.hpp"
#include "Player.hpp"

SpaceShipPart::SpaceShipPart(Position p, DisplayManager &dm, vector<string> sprites, uint width, uint height) : Interactable(p, dm, sprites), CollisionBox(width, height) {}

void SpaceShipPart::grab(Player &grabber)
{
    grabbed = true;
    // TODO : add to player inventory
}

void SpaceShipPart::interact(Player &interactor)
{
    grab(interactor);
}

void SpaceShipPart::update(float deltaTime) {}

void SpaceShipPart::render()
{
    if (!grabbed)
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
    }
}

void SpaceShipPart::reverseMotion(){};