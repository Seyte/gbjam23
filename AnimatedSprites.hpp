#ifndef ANIMATEDSPRITES_HPP
#define ANIMATEDSPRITES_HPP

#include "Sprite.hpp"
#include <vector>
using namespace std;

class AnimatedSprites
{
private:
    int numberOfSprites{0};
    int currentAnimationStage{0};
    vector<string> sprites;
    float timeSinceLastAnimation{0};

public:
    AnimatedSprites();
    AnimatedSprites(vector<string> _sprites);
    void update(float deltaTime);
    string getTextureString();
};

#endif
