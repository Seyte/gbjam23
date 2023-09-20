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
    int _width;
    int _height;

public:
    Sprite(string path, SDL_Texture *imageSurface, int width, int height);
    SDL_Texture* getTexture();
    int getWidth();
    int getHeight();
    ~Sprite();
};

#endif