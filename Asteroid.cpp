#define ASTEROID_SPEED 4
#define ASTEROID_ACCELERATION_DECREASE 4
#define ASTEROID_MAX_ACCELERATION 20
#define ASTEROID_WIDTH 27
#define ASTEROID_HEIGHT 27
#include "Asteroid.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
Asteroid::Asteroid(Position p, DisplayManager &dm) : DynamicGameObject(p, dm, {},ASTEROID_ACCELERATION_DECREASE,ASTEROID_SPEED,ASTEROID_MAX_ACCELERATION), CollisionBox(ASTEROID_WIDTH, ASTEROID_HEIGHT)
{
    srand(std::time(0));
    _sprite_number = (uint)(rand() % 4 + 1);
}

void Asteroid::render(){
    string image = "asteroid" + std::to_string(_sprite_number) + ".png";
    getDisplayManager().setTexture(image, (uint)getPosition().getX(), (uint)getPosition().getY());
}

void Asteroid::bounce(int direction){
    DynamicGameObject::bounce(direction);
}