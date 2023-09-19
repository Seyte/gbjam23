#include "DisplayManager.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

#define SCALE_FACTOR 5

#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144

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

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

App app;
SDL_Rect destinationRect;
SDL_Texture* test;
Sprite* s;
void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = SDL_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", 0);
    if (SDL_RenderSetLogicalSize(app.renderer, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT) != 0)
    {
        printf("Failed to resize renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

DisplayManager::DisplayManager() : _cameraOffset(Position(0, 0))
{
    memset(&app, 0, sizeof(App));
    initSDL();
    // load all sprites
    std::string path = PATH_TO_RESOURCE_DIR;
    for (const auto &entry : fs::directory_iterator(path))
    {   
        string filename = entry.path().string();
        std::cout << "loading " << filename << " | is png?" << fileEndsWithSuffix(filename, FILE_SUFFIX) << std::endl;
        if(fileEndsWithSuffix(filename, FILE_SUFFIX)){
            
            SDL_Surface* imageSurface = IMG_Load(filename.c_str());
            if (!imageSurface) {
                cout << "Failed to load image: " << filename << endl;
                exit(1);
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, imageSurface);
            //SDL_FreeSurface(imageSurface);
            s = new Sprite(filename,texture);
            test = (*s).getTexture();
            destinationRect = {0, 0, imageSurface->w, imageSurface->h}; 
    
        }
    }
}

void DisplayManager::setCameraOffset(const Position &p)
{
    _cameraOffset = p;
}

const Position &DisplayManager::getCameraOffset()
{
    return _cameraOffset;
}

void DisplayManager::render()
{
    SDL_RenderPresent(app.renderer);
    if (SDL_SetRenderDrawColor(app.renderer, DEFAULT_COLOR_R, DEFAULT_COLOR_G, DEFAULT_COLOR_B, 255) < 0)
    {
        printf("Failed to pick the color: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(app.renderer);
    SDL_RenderCopy(app.renderer, test, NULL, &destinationRect);
}

DisplayManager::~DisplayManager()
{
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
}

void DisplayManager::setPixel(int x, int y, Color color)
{
    if (x < 0 || y < 0 || x >= DEFAULT_SCREEN_WIDTH || y >= DEFAULT_SCREEN_HEIGHT)
    {
        return;
    }

    if (SDL_SetRenderDrawColor(app.renderer, color._r, color._g, color._b, 255) < 0)
    {
        printf("Failed to pick the color: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Rect rect = {x, y, 1, 1};

    if (SDL_RenderFillRect(app.renderer, &rect) < 0)
    {
        printf("Failed to draw a point: %s\n", SDL_GetError());
        exit(1);
    }
}

void DisplayManager::setTexture(uint leftCornerX, uint leftCornerY, Color *colorMatrix, uint width, uint height)
{
    (void)leftCornerX;
    (void)leftCornerY;
    (void)colorMatrix;
    (void)width;
    (void)height;
}
