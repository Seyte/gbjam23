#include "Player.hpp"
#include <stdio.h>
#include <cmath>
#include <iostream>
#define SPEED 30
#define ACCELERATION_DECREASE 1
#define MAX_ACCELERATION 60

using namespace std;

Player::Player(Position p, DisplayManager &dm, uint width, uint height) : GameObject(p, dm), CollisionBox(width, height), _direction(0, 0), _accelerationX(0), _accelerationY(0), _pixelToTravelX(0), _pixelToTravelY(0)
{
}

void Player::render()
{
    getDisplayManager().setTexture("rocketman.png", (uint)getPosition().getX(), (uint)getPosition().getY());
}

void Player::update(float deltaTime)
{
    // Decreasing acceleration from floating in the air
    if (_accelerationX > 0)
    {
        _accelerationX -= ACCELERATION_DECREASE * deltaTime;
        if (_accelerationX <= 0)
        {
            _accelerationX = 0;
        }
    }
    else if (_accelerationX < 0)
    {
        _accelerationX += ACCELERATION_DECREASE * deltaTime;
        if (_accelerationX >= 0)
        {
            _accelerationX = 0;
        }
    }

    if (_accelerationY > 0)
    {
        _accelerationY -= ACCELERATION_DECREASE * deltaTime;
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
        _accelerationY += ACCELERATION_DECREASE * deltaTime;
    }
    // Increasing acceleration if any key pressed

    _accelerationX += _direction.getX() * SPEED * deltaTime;
    _accelerationY += _direction.getY() * SPEED * deltaTime;
    // cap the acceleration
    if (_accelerationX >= MAX_ACCELERATION)
    {
        _accelerationX = MAX_ACCELERATION;
    }
    if (_accelerationX <= -MAX_ACCELERATION)
    {
        _accelerationX = -MAX_ACCELERATION;
    }
    if (_accelerationY >= MAX_ACCELERATION)
    {
        _accelerationY = MAX_ACCELERATION;
    }
    if (_accelerationY <= -MAX_ACCELERATION)
    {
        _accelerationY = -MAX_ACCELERATION;
    }
    // update the number of pixel to travel
    _pixelToTravelX += _accelerationX * deltaTime;
    _pixelToTravelY += _accelerationY * deltaTime;
    // remove |_pixelToTravelX| from _pixelToTravelX (same for Y)
    float travelX = floor(_pixelToTravelX);
    _pixelToTravelX -= travelX;
    float travelY = floor(_pixelToTravelY);
    _pixelToTravelY -= travelY;
    setPosition(Position(getPosition().getX() + (int)travelX, getPosition().getY() + (int)travelY));
}

void Player::setDirection(const Position &d)
{
    _direction = d;
}