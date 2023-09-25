#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "utils.hpp"
#include "Interactable.hpp"
#include <algorithm>

class SpaceShip : public Interactable, public CollisionBox
{
private:
    string _fixedSprite;
    int _fixablePartID;
    bool _fixed = false;
    Position _interactionPoint;

public:
    SpaceShip(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites, string fixedSprite, int distance, int fixablePartID, Position interactionPoint);
    void update(float deltaTime);
    void render();
    void bounce(int direction);
    void interact(Player &interactor);
    void grab(Player &grabber);
    Position getInteractionPoint();
};

#endif