#include "Position.hpp"

Position::Position(int x, int y) : _x(x), _y(y) {}

Position::Position(Position &p) : _x(p.getX()), _y(p.getY()) {}

int Position::getX() { return _x; }

int Position::getY() { return _y; }

void Position::setX(int x) { _x = x; }

void Position::setY(int y) { _y = y; }

Position &Position::operator=(const Position &p)
{
    _x = p._x;
    _y = p._y;
    return *this;
}
bool Position::operator==(const Position& p) {
    return (this->getX() == p._x) && (this->getY() == p._y);
}