#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include "Color.hpp"
#include <string>
#include "Sprite.hpp"

typedef unsigned int uint;
using namespace std;
class DisplayManager
{
private:
    Color *_displayMatrix;
    unordered_map<string, Sprite> _spriteTable;
    void prepareScene();
public:
    DisplayManager();
    void render();
    Color getPixel(uint x, uint y);
    void setPixel(uint x, uint y, Color color);
    void setTexture(uint leftCornerX, uint leftCornerY, Color *colorMatrix, uint width, uint height);
    virtual ~DisplayManager();
};

#endif