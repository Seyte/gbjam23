#include "DynamicGameObject.hpp"

DynamicGameObject::DynamicGameObject(Position p, DisplayManager &dm, vector<string> sprites, float accelerationDecrease, float speed, float maxSpeed) : GameObject(p, dm, sprites), _direction(0, 0), _accelerationX(0), _accelerationY(0), _pixelToTravelX(0), _pixelToTravelY(0), _accelerationDecrease(accelerationDecrease), _speed(speed), _maxSpeed(maxSpeed) {}
void DynamicGameObject::update(float deltaTime)
{
    // Decreasing acceleration from floating in the air
    if (_accelerationX > 0)
    {
        _accelerationX -= _accelerationDecrease * deltaTime;
        if (_accelerationX <= 0)
        {
            _accelerationX = 0;
        }
    }
    else if (_accelerationX < 0)
    {
        _accelerationX += _accelerationDecrease * deltaTime;
        if (_accelerationX >= 0)
        {
            _accelerationX = 0;
        }
    }

    if (_accelerationY > 0)
    {
        _accelerationY -= _accelerationDecrease * deltaTime;
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
        _accelerationY += _accelerationDecrease * deltaTime;
    }
    // Increasing acceleration if any key pressed

    _accelerationX += _direction.getX() * _speed * deltaTime;
    _accelerationY += _direction.getY() * _speed * deltaTime;
    // cap the acceleration
    if (_accelerationX >= _maxSpeed)
    {
        _accelerationX = _maxSpeed;
    }
    if (_accelerationX <= -_maxSpeed)
    {
        _accelerationX = -_maxSpeed;
    }
    if (_accelerationY >= _maxSpeed)
    {
        _accelerationY = _maxSpeed;
    }
    if (_accelerationY <= -_maxSpeed)
    {
        _accelerationY = -_maxSpeed;
    }
    // update the number of pixel to travel
    _pixelToTravelX += _accelerationX * deltaTime;
    _pixelToTravelY += _accelerationY * deltaTime;
    // remove |_pixelToTravelX| from _pixelToTravelX (same for Y)
    float travelX = floor(_pixelToTravelX);
    _pixelToTravelX -= travelX;
    float travelY = floor(_pixelToTravelY);
    _pixelToTravelY -= travelY;

    int newX = getPosition().getX() + (int)travelX;
    int newY = getPosition().getY() + (int)travelY;
    requestMove(Position(newX, newY));

    _sprites.update(deltaTime);
}

void DynamicGameObject::setDirection(const Position &d)
{
    _direction = d;
}
void DynamicGameObject::reverseXAcceleration()
{
    _accelerationX = -_accelerationX;
}
void DynamicGameObject::reverseYAcceleration()
{
    _accelerationY = -_accelerationY;
}

void DynamicGameObject::bounce(int direction)
{
    if (direction & LEFT)
    {
        reverseXAcceleration();
        _direction.setX(-_direction.getX());
    }
    if (direction & RIGHT)
    {
        reverseXAcceleration();
        _direction.setX(-_direction.getX());
    }
    if (direction & TOP)
    {
        reverseYAcceleration();
        _direction.setY(-_direction.getY());
    }
    if (direction & DOWN)
    {
        reverseYAcceleration();
        _direction.setY(-_direction.getY());
    }
}