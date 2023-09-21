#include "CollisionBox.hpp"

CollisionBox::CollisionBox(uint width, uint height) : _width(width), _height(height) {}

uint CollisionBox::getWidth() { return _width; }

uint CollisionBox::getHeight() { return _height; }