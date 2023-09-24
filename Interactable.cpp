#include "Interactable.hpp"

Interactable::Interactable(Position p, DisplayManager &dm, vector<string> sprites, int distance, int objwidth, int objheight) : GameObject(p, dm, sprites), interactionDistance(distance), width(objwidth), height(objheight) {}