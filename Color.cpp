#include "Color.hpp"

// TODO: instead of 0 0 0 we should have a default color for the palette.
Color::Color() : _r(0), _g(0), _b(0)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b) : _r(r), _g(g), _b(b) {}