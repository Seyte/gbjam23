#ifndef DYNAMIC_GAMEOBJECT_HPP
#define DYNAMIC_GAMEOBJECT_HPP
#include "GameObject.hpp"
class DynamicGameObject : public GameObject
{
private:
    Position _direction;
    float _accelerationX;
    float _accelerationY;
    float _pixelToTravelX;
    float _pixelToTravelY;
    float _accelerationDecrease;
    float _speed;
    float _maxSpeed;

public:
    DynamicGameObject(Position p, DisplayManager &dm, vector<string> sprites, float accelerationDecrease, float speed, float maxSpeed);
    void update(float deltaTime);
    virtual void render() = 0;
    void setDirection(const Position &d);
    void reverseXAcceleration();
    void reverseYAcceleration();
    void bounce(int direction);
};

#endif