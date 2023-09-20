#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include "Color.hpp"
#include "Position.hpp"
#include <string>
#include "Sprite.hpp"
#include "SDL.h"
#include "SDL_image.h"

typedef unsigned int uint;
using namespace std;
class DisplayManager
{
private:
    unordered_map<string, Sprite> _spriteTable;
    Position _cameraOffset;
    void prepareScene();

public:
    DisplayManager();
    void render();
    void setCameraOffset(const Position &p);
    const Position &getCameraOffset();
    void setPixel(int x, int y, Color color);
    void setTexture(string filename, uint leftCornerX, uint leftCornerY);
    virtual ~DisplayManager();
};

#endif