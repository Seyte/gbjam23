#ifndef ANIMATEDSPRITES_HPP
#define ANIMATEDSPRITES_HPP


#include "Sprite.hpp"
#include <vector>
using namespace std;

class AnimatedSprites
{
private:
    int numberOfSprites;
    vector<Sprite> sprites;

public:
    void update(int deltaTime);
    SDL_Texture* getTexture();
    ~AnimatedSprites();
};

#endif
