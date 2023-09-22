#include "AnimatedSprites.hpp"
#include "Sprite.hpp"

using namespace std;

#define ANIMATIONS_PER_SEC 1

AnimatedSprites::AnimatedSprites(vector<string> _sprites)
{
    sprites = _sprites;
    numberOfSprites = 3;
    currentAnimationStage = 0;
}

void AnimatedSprites::update(float deltaTime)
{
    if (deltaTime >= 1000 / ANIMATIONS_PER_SEC)
    {
        currentAnimationStage++;
    }

    if (currentAnimationStage >= numberOfSprites)
    {
        currentAnimationStage = 0;
    }
}

string AnimatedSprites::getTextureString()
{
    sprites.at(currentAnimationStage);
}
