#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include "Color.hpp"
#include "Position.hpp"
#include <string>
#include <unordered_map>
#include "Sprite.hpp"
#include "SDL.h"
#include "SDL_image.h"

#define SCALE_FACTOR 5

#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144

#define WORLD_WIDTH 960
#define WORLD_HEGIHT 144

#define DEFAULT_SCREEN_PIXEL_COUNT DEFAULT_SCREEN_WIDTH *DEFAULT_SCREEN_HEIGHT

#define SCREEN_WIDTH DEFAULT_SCREEN_WIDTH *SCALE_FACTOR
#define SCREEN_HEIGHT DEFAULT_SCREEN_HEIGHT *SCALE_FACTOR

#define WINDOW_NAME "Game"
// TODO: we need to see how to make this work when we execute the main from any file. will have to discuss
#define PATH_TO_RESOURCE_DIR "./resources/"
#define FILE_SUFFIX ".png"

#define POSITION_TO_INDEX(x, y) ((y)*DEFAULT_SCREEN_WIDTH + (x))

#define DEFAULT_COLOR_R 0
#define DEFAULT_COLOR_G 0
#define DEFAULT_COLOR_B 0

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
    void setCameraOffset(Position p);
    Position getCameraOffset();
    void setPixel(int x, int y, Color color);
    void setTexture(string filename, uint leftCornerX, uint leftCornerY);
    virtual ~DisplayManager();
};

#endif
