#include "Player.hpp"
#include <stdio.h>
#include <cmath>
#include <iostream>
#define PLAYER_SPEED 30
#define PLAYER_ACCELERATION_DECREASE 1
#define PLAYER_MAX_ACCELERATION 60

using namespace std;

Player::Player(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites) : DynamicGameObject(p, dm, sprites, PLAYER_ACCELERATION_DECREASE, PLAYER_SPEED, PLAYER_MAX_ACCELERATION), CollisionBox(width, height)
{
}

void Player::render()
{
    int dir = getAccDirection();

    switch (dir)
    {
    case DOWN:
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY());
        break;
    case TOP:
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 180);
        break;
    case RIGHT:
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 270);
        break;
    case LEFT:
        getDisplayManager().setTexture(_sprites.getTextureString(), (uint)getPosition().getX(), (uint)getPosition().getY(), 90);
        break;
    default:
        getDisplayManager().setTexture("spacedude.png", (uint)getPosition().getX(), (uint)getPosition().getY());
        break;
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
