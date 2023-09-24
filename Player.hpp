#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "GameObject.hpp"
#include "CollisionBox.hpp"
#include "Position.hpp"

class Player : public GameObject, public CollisionBox
{
private:
    Position _direction;
    float _accelerationX;
    float _accelerationY;
    float _pixelToTravelX;
    float _pixelToTravelY;
    vector<int> inventory;

public:
    Player(Position p, DisplayManager &dm, uint width, uint height, vector<string> sprites);
    void update(float deltaTime);
    void render();
    void setDirection(const Position &d);
    void bounce(int direction);
    void addToInventory(int id);
    vector<int> &getInventory();
};

#endif