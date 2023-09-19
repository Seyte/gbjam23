#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <string>

using namespace std;
#include "SDL_image.h"

class Sprite
{
private:
    string _path;
    SDL_Texture *_texture;

public:
    Sprite(string path, SDL_Texture *imageSurface);
    SDL_Texture* getTexture();
    ~Sprite();
};

#endif