#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "GameObject.hpp"
#include "Position.hpp"

class Player : public GameObject
{
private:
    Position _direction;
    float _accelerationX;
    float _accelerationY;
    float _pixelToTravelX;
    float _pixelToTravelY;
public:
    Player(Position p);
    void update(int deltaTime);
    void render();
    void setDirection(const Position &d);
};

#endif