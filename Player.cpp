#include "Player.hpp"
#include <stdio.h>
#define SPEED 10
#define ACCELERATION_DECREASE 0.1
Player::Player(Position p) : GameObject(p), _direction(0, 0), _accelerationX(0), _accelerationY(0), _pixelToTravelX(0), _pixelToTravelY(0)
{
}

void Player::render() {}

void Player::update(int deltaTime)
{
    if (_accelerationX > 0)
    {
        _accelerationX -= ACCELERATION_DECREASE;
        if (_accelerationX <= 0)
        {
            _accelerationX = 0;
        }
    }
    else if (_accelerationX < 0)
    {
        _accelerationX += ACCELERATION_DECREASE;
        if (_accelerationX >= 0)
        {
            _accelerationX = 0;
        }
    }

    if (_accelerationY > 0)
    {
        _accelerationY -= ACCELERATION_DECREASE;
        if (_accelerationY <= 0)
        {
            _accelerationY = 0;
        }
    }
    else if (_accelerationY < 0)
    {
        if (_accelerationY >= 0)
        {
            _accelerationY = 0;
        }
        _accelerationY += ACCELERATION_DECREASE;
    }
    setPosition(Position(getPosition().getX() + _direction.getX(), getPosition().getY() + _direction.getY()));
}

void Player::setDirection(const Position &d)
{
    _direction = d;
}