#include "AnimatedSprites.hpp"
#include "Sprite.hpp"

using namespace std;

AnimatedSprites::AnimatedSprites(Sprite *s1, Sprite *s2, Sprite *s3){
    sprites.add(s1);
    sprites.add(s2);
    sprites.add(s3);
    numberOfSprites = 3;
}

void AnimatedSprites::update(int deltaTime)
