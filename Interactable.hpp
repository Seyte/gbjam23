#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "GameObject.hpp"
#include "Player.hpp"

class Interactable : public GameObject
{
public:
    bool grabbed = false;
    int interactionDistance;
    int width;
    int height;
    Interactable(Position p, DisplayManager &dm, vector<string> sprites, int distance, int objwidth, int objheight);
    virtual void interact(Player &interactor) = 0;
    virtual void grab(Player &grabber) = 0;
};
#endif