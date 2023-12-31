#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include <string>
#include <unordered_map>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Sprite.hpp"
#include "utils.hpp"
#include "Color.hpp"
#include "Position.hpp"

#define WINDOW_NAME "Game"
// TODO: we need to see how to make this work when we execute the main from any file. will have to discuss
#define PATH_TO_RESOURCE_DIR "./resources/"
#define FILE_SUFFIX ".png"

#define DEFAULT_COLOR_R 0
#define DEFAULT_COLOR_G 0
#define DEFAULT_COLOR_B 0

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
    void setTexture(string filename, uint leftCornerX, uint leftCornerY, double angle = 0);
    Sprite *getSprite(string filename);
    void setText(string text, int fontSize, Position p, int width, int height);
    void playSound(string sound);
    virtual ~DisplayManager();
};

#endif
