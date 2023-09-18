#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include "Color.hpp"
typedef unsigned int uint;

class DisplayManager
{
private:
    Color *_displayMatrix;
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