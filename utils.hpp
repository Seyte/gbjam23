#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
// TODO: delete this

#define SCALE_FACTOR 5

#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144

#define WORLD_WIDTH 960
#define WORLD_HEGIHT 144

#define DEFAULT_SCREEN_PIXEL_COUNT DEFAULT_SCREEN_WIDTH *DEFAULT_SCREEN_HEIGHT

#define SCREEN_WIDTH DEFAULT_SCREEN_WIDTH *SCALE_FACTOR
#define SCREEN_HEIGHT DEFAULT_SCREEN_HEIGHT *SCALE_FACTOR

#define POSITION_TO_INDEX_SCREEN(x, y) ((y)*DEFAULT_SCREEN_WIDTH + (x))

#define POSITION_TO_INDEX_WORLD(x, y) ((y+1)*(WORLD_WIDTH+2) + (x)+1)

#define RIGHT 1
#define RIGHT_OFFSET 0
#define LEFT 2
#define LEFT_OFFSET 1
#define TOP 4
#define TOP_OFFSET 2
#define DOWN 8
#define DOWN_OFFSET 3

typedef unsigned int uint;

using namespace std;

bool fileEndsWithSuffix(string file, string suffix);
#endif