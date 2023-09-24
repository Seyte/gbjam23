#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "DynamicGameObject.hpp"
#include "CollisionBox.hpp"
#include "Position.hpp"

class Player : public DynamicGameObject, public CollisionBox
{
private:
    vector<int> inventory;

public:
    Player(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites);
    void update(float deltaTime);
    void render();
    void addToInventory(int id);
    vector<int> &getInventory();
};

#endif