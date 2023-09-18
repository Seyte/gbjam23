#include "DisplayManager.hpp"
#include "SDL.h"

using namespace std;

#define SCALE_FACTOR 5

#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144

#define DEFAULT_SCREEN_PIXEL_COUNT DEFAULT_SCREEN_WIDTH *DEFAULT_SCREEN_HEIGHT

#define SCREEN_WIDTH DEFAULT_SCREEN_WIDTH *SCALE_FACTOR
#define SCREEN_HEIGHT DEFAULT_SCREEN_HEIGHT *SCALE_FACTOR

#define WINDOW_NAME "Game"

#define POSITION_TO_INDEX(x, y) ((y)*DEFAULT_SCREEN_WIDTH + (x))

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

App app;

void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

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
}

void renderScene(void)
{
    SDL_RenderPresent(app.renderer);
}

DisplayManager::DisplayManager()
{

    memset(&app, 0, sizeof(App));
    _displayMatrix = new Color[DEFAULT_SCREEN_PIXEL_COUNT];
    for (uint i = 0; i < DEFAULT_SCREEN_PIXEL_COUNT; i++)
    {
        _displayMatrix[i] = Color();
    }
    initSDL();
}

void DisplayManager::prepareScene()
{
    // performancewise : not the best, but most probably easier to adapt to our own game console.

    for (int h = 0; h < DEFAULT_SCREEN_HEIGHT; h++)
    {
        for (int w = 0; w < DEFAULT_SCREEN_WIDTH; w++)
        {
            Color color = _displayMatrix[POSITION_TO_INDEX(w, h)];

            if (SDL_SetRenderDrawColor(app.renderer, color._r, color._g, color._b, 255) < 0)
            {
                printf("Failed to pick the color: %s\n", SDL_GetError());
                exit(1);
            }
            SDL_Rect rect = {w * SCALE_FACTOR, h * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};

            if (SDL_RenderFillRect(app.renderer, &rect) < 0)
            {
                printf("Failed to draw a point: %s\n", SDL_GetError());
                exit(1);
            }
        }
    }
}

void DisplayManager::render()
{
    prepareScene();
    renderScene();
}

DisplayManager::~DisplayManager()
{
    if (_displayMatrix != NULL)
    {
        delete[] _displayMatrix;
        _displayMatrix = NULL;
    }
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
}

// TODO : modifier cette méthode, aussi attention aux & pour éviter de faire des copies systématiques
Color DisplayManager::getPixel(uint x, uint y)
{
    // may crash on bad value for x and y. i don't know if we need this method rn, i'll keep it and we can delete it later if needed.
    return _displayMatrix[POSITION_TO_INDEX(x, y)];
}

void DisplayManager::setPixel(uint x, uint y, Color color)
{
    if (x >= DEFAULT_SCREEN_WIDTH || y >= DEFAULT_SCREEN_HEIGHT)
    {
        return;
    }
    _displayMatrix[POSITION_TO_INDEX(x, y)] = color;
}

void DisplayManager::setTexture(uint leftCornerX, uint leftCornerY, Color *colorMatrix, uint width, uint height)
{
    (void)leftCornerX;
    (void)leftCornerY;
    (void)colorMatrix;
    (void)width;
    (void)height;
}
