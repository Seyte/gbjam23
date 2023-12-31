#include "AnimatedSprites.hpp"
#include "Sprite.hpp"

using namespace std;

#define ANIMATIONS_PER_SEC 1

AnimatedSprites::AnimatedSprites()
{
}

AnimatedSprites::AnimatedSprites(vector<string> _sprites) : numberOfSprites(static_cast<int>(_sprites.size())), sprites(_sprites)
{
}

void AnimatedSprites::update(float deltaTime)
{
    timeSinceLastAnimation += deltaTime;
    if (timeSinceLastAnimation >= ((float)1 / (float)ANIMATIONS_PER_SEC))
    {
        currentAnimationStage++;
        timeSinceLastAnimation -= ((float)1 / (float)ANIMATIONS_PER_SEC);
    }

    if (currentAnimationStage >= numberOfSprites)
    {
        currentAnimationStage = 0;
    }
}

string AnimatedSprites::getTextureString()
{
    if (numberOfSprites > 0)
        return sprites.at(currentAnimationStage);
    else
        return NULL;
}
