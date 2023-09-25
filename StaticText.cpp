#include "StaticText.hpp"
#include "DisplayManager.hpp"

StaticText::StaticText(string text, Position p, int width, int height, bool display, DisplayManager &dm) : GameObject(p, dm), _text(text), _width(width), _height(height), _display(display)
{
}

void StaticText::update(float deltaTime)
{
    (void)deltaTime;
}

void StaticText::render()
{
    if (_display)
    {
        getDisplayManager().setText(_text, getPosition(), _width, _height);
    }
}

bool StaticText::getDisplay()
{
    return _display;
}

void StaticText::setDisplay(bool display)
{
    _display = display;
}

void StaticText::bounce(int direction) { (void)direction; }