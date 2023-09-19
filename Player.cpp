#include "Player.hpp"
#include <stdio.h>

Player::Player(Position p) : GameObject(p), _direction(0, 0)
{
}
void Player::render() {}

void Player::update(int deltaTime)
{
    (void)deltaTime;
    setPosition(Position(getPosition().getX() + _direction.getX(), getPosition().getY() + _direction.getY()));
}

void Player::setDirection(const Position& d)
{
    _direction = d;
}