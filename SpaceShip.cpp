#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites, string fixedSprite, int distance, int fixablePartID, Position interactionPoint) : Interactable(p, dm, sprites, distance, width, height), CollisionBox(width, height), _fixedSprite(fixedSprite), _fixablePartID(fixablePartID), _interactionPoint(interactionPoint) {}

void SpaceShip::update(float deltaTime)
{
    _sprites.update(deltaTime);
}

void SpaceShip::render()
{
    if (!_fixed)
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
    }
    else
    {
        getDisplayManager().setTexture(_fixedSprite, (uint)getPosition().getX(), (uint)getPosition().getY());
    }
}

void SpaceShip::bounce(int direction) { (void)direction; }

void SpaceShip::interact(Player &interactor)
{
    if (!_fixed && count(interactor.getInventory().begin(), interactor.getInventory().end(), _fixablePartID))
    {
        interactor.getInventory().erase(std::remove(interactor.getInventory().begin(), interactor.getInventory().end(), _fixablePartID), interactor.getInventory().end());
        _fixed = true;
        getDisplayManager().playSound("fix");
    }
}

bool SpaceShip::isFixed()
{
    return _fixed;
}

void SpaceShip::grab(Player &grabber) { (void)grabber; }

Position SpaceShip::getInteractionPoint()
{
    return _interactionPoint;
}
