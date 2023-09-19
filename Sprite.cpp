#include "Sprite.hpp"

Sprite::Sprite(string path, SDL_Texture *texture) : _path(path) {
    _texture = texture;
}

SDL_Texture* Sprite::getTexture(){
    return _texture;
}

Sprite::~Sprite(){
    SDL_DestroyTexture(_texture);
}
