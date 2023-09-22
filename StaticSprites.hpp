#ifndef STATIC_SPRITES_HPP
#define STATIC_SPRITES_HPP
#include "GameObject.hpp"
#include "Position.hpp"
#include <string>

using namespace std;

class StaticSprites : public GameObject
{
private:
    string _filename;
public:
    StaticSprites(Position p,string filename,DisplayManager & dm);
    void update(float deltaTime);
    void render();
    void reverseMotion();
};

#endif