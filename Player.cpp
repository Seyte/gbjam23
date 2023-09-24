#include "Player.hpp"
#include <stdio.h>
#include <cmath>
#include <iostream>
#define PLAYER_SPEED 30
#define PLAYER_ACCELERATION_DECREASE 1
#define PLAYER_MAX_ACCELERATION 60

using namespace std;

Player::Player(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites) : DynamicGameObject(p, dm, sprites,PLAYER_ACCELERATION_DECREASE,PLAYER_SPEED,PLAYER_MAX_ACCELERATION), CollisionBox(width, height)
{
}

void Player::render()
{
    if (_direction == Position(0, 0))
    {
        getDisplayManager().setTexture("rocketman.png", (uint)getPosition().getX(), (uint)getPosition().getY());
    }
    else if (_direction == Position(1, 0))
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 270);
    }
    else if (_direction == Position(0, 1))
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
    }
    else if (_direction == Position(-1, 0))
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 90);
    }
    else if (_direction == Position(0, -1))
    {
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 180);
    }
}

void Player::update(float deltaTime)
{
    DynamicGameObject::update(deltaTime);
    _sprites.update(deltaTime);
}

void Player::addToInventory(int id)
{
    inventory.push_back(id);
}

vector<int> &Player::getInventory()
{
    return inventory;
}
