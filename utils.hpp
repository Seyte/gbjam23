#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

#define SCALE_FACTOR 5

#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144

#define WORLD_WIDTH 960
#define WORLD_HEGIHT 144

#define DEFAULT_SCREEN_PIXEL_COUNT DEFAULT_SCREEN_WIDTH *DEFAULT_SCREEN_HEIGHT

#define SCREEN_WIDTH DEFAULT_SCREEN_WIDTH *SCALE_FACTOR
#define SCREEN_HEIGHT DEFAULT_SCREEN_HEIGHT *SCALE_FACTOR

#define POSITION_TO_INDEX(x, y) ((y)*DEFAULT_SCREEN_WIDTH + (x))

typedef unsigned int uint;

using namespace std;

bool fileEndsWithSuffix(string file, string suffix);
void printCollisionMap(int collisionMap[]);
#endif