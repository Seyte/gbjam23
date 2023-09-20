#include "Sprite.hpp"

Sprite::Sprite(string path, SDL_Texture *texture, int width, int height) : _path(path), _width(width), _height(height)
{
    printf("Le constructeur de Sprite est appelé\n");
    _texture = texture;
}

SDL_Texture *Sprite::getTexture()
{
    return _texture;
}

int Sprite::getWidth()
{
    return _width;
}
int Sprite::getHeight()
{
    return _height;
}

Sprite::~Sprite()
{
    printf("Le destructeur de Sprite est appelé\n");
    SDL_DestroyTexture(_texture);
}
