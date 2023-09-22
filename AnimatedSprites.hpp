#ifndef ANIMATEDSPRITES_HPP
#define ANIMATEDSPRITES_HPP

#include "Sprite.hpp"
#include <vector>
using namespace std;

class AnimatedSprites
{
private:
    int numberOfSprites;
    int currentAnimationStage;
    vector<string> sprites;

public:
    void update(float deltaTime);
    string getTextureString();
};

#endif
