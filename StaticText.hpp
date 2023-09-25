#ifndef STATIC_TEXT_HPP
#define STATIC_TEXT_HPP
#include "GameObject.hpp"
#include "Position.hpp"
#include <string>

using namespace std;

class StaticText : public GameObject
{
private:
    string _text;
    int _size;
    int _width;
    int _height;
    bool _display;

public:
    StaticText(string text, int size, Position p, int width, int height, bool display, DisplayManager &dm);
    void update(float deltaTime);
    void render();
    void bounce(int direction);
    bool getDisplay();
    void setDisplay(bool display);
};

#endif