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
    unordered_map<string, Sprite> _spriteTable;
    void prepareScene();
public:
    DisplayManager();
    void render();
    void setPixel(int x, int y, Color color);
    void setTexture(uint leftCornerX, uint leftCornerY, Color *colorMatrix, uint width, uint height);
    virtual ~DisplayManager();
};

#endif