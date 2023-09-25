#include "utils.hpp"
#include <math.h>

bool fileEndsWithSuffix(string file, string suffix)
{
    // file name long enough?
    if (file.length() > suffix.length())
    {
        return (file.compare(file.length() - suffix.length(), suffix.length(), suffix) == 0);
    }
    return false;
}

double getDistance(Position p1, uint w1, uint h1, Position p2, uint w2, uint h2)
{
    int x1 = p1.getX() + (w1 / 2);
    int y1 = p1.getY() + (h1 / 2);
    int x2 = p2.getX() + (w2 / 2);
    int y2 = p2.getY() + (h2 / 2);
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double getDistance(Position p1, Position p2)
{
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}
