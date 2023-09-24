#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites, int distance, int fixablePartID) : Interactable(p, dm, sprites, distance, width, height), CollisionBox(width, height), _fixablePartID(fixablePartID) {}

void SpaceShip::update(float deltaTime)
{
    _sprites.update(deltaTime);
}

void SpaceShip::render()
{
    if (!fixed)
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
    }
    else
    {
        getDisplayManager().setTexture("rocket_fixed.png", (uint)getPosition().getX(), (uint)getPosition().getY());
    }
}

void SpaceShip::bounce(int direction) { (void)direction; }

void SpaceShip::interact(Player &interactor)
{
    if (!fixed && count(interactor.getInventory().begin(), interactor.getInventory().end(), _fixablePartID))
    {
        interactor.getInventory().erase(std::remove(interactor.getInventory().begin(), interactor.getInventory().end(), _fixablePartID), interactor.getInventory().end());
        fixed = true;
    }
}

void SpaceShip::grab(Player &grabber) { (void)grabber; }
