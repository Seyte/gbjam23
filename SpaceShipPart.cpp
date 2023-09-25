#include "SpaceShipPart.hpp"
#include "Player.hpp"

SpaceShipPart::SpaceShipPart(Position p, DisplayManager &dm, vector<string> sprites, int distance, uint width, uint height) : Interactable(p, dm, sprites, distance, width, height), CollisionBox(width, height) {}

void SpaceShipPart::grab(Player &grabber)
{
    grabbed = true;
    grabber.addToInventory(getId());
}

void SpaceShipPart::interact(Player &interactor)
{
    grab(interactor);
}

void SpaceShipPart::update(float deltaTime) { (void)deltaTime; }

void SpaceShipPart::render()
{
    if (!grabbed)
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
    }
}

void SpaceShipPart::bounce(int direction) { (void)direction; }

Position SpaceShipPart::getInteractionPoint()
{
    return Position(getPosition().getX() + (width / 2), getPosition().getY() + (height / 2));
}