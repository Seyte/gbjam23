#include "DisplayManager.hpp"
#include "Sprite.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

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
    cout << "Constructeur DisplayManager" << endl;
    memset(&app, 0, sizeof(App));
    initSDL();
    // load all sprites
    std::string path = PATH_TO_RESOURCE_DIR;
    for (const auto &entry : fs::directory_iterator(path))
    {
        string filename = entry.path().string();
        std::cout << "loading " << filename << " | is png?" << fileEndsWithSuffix(filename, FILE_SUFFIX) << std::endl;
        if (fileEndsWithSuffix(filename, FILE_SUFFIX))
        {

            SDL_Surface *imageSurface = IMG_Load(filename.c_str());
            if (!imageSurface)
            {
                cout << "Failed to load image: " << filename << endl;
                exit(1);
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, imageSurface);
            filename.erase(0, (sizeof(PATH_TO_RESOURCE_DIR) - 1) / sizeof(char));
            _spriteTable.emplace(filename, *(new Sprite(filename, texture, imageSurface->w, imageSurface->h)));
            SDL_FreeSurface(imageSurface);
        }
    }
}

void DisplayManager::setCameraOffset(Position p)
{
    _cameraOffset.setX(p.getX());
    _cameraOffset.setY(p.getY());
    // world borders
    if (_cameraOffset.getX() < 0)
    {
        _cameraOffset.setX(0);
    }
    if (_cameraOffset.getY() < 0)
    {
        _cameraOffset.setY(0);
    }
    if (_cameraOffset.getX() + DEFAULT_SCREEN_WIDTH > WORLD_WIDTH)
    {
        _cameraOffset.setX(WORLD_WIDTH - DEFAULT_SCREEN_WIDTH);
    }
    if (_cameraOffset.getY() + DEFAULT_SCREEN_HEIGHT > WORLD_HEGIHT)
    {
        _cameraOffset.setY(WORLD_HEGIHT - DEFAULT_SCREEN_HEIGHT);
    }
}

Position DisplayManager::getCameraOffset()
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
}

DisplayManager::~DisplayManager()
{
    _spriteTable.clear();

    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
}

void DisplayManager::setPixel(int x, int y, Color color)
{

    if (SDL_SetRenderDrawColor(app.renderer, color._r, color._g, color._b, 255) < 0)
    {
        printf("Failed to pick the color: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Rect rect = {x - getCameraOffset().getX(), y - getCameraOffset().getY(), 1, 1};

    if (SDL_RenderFillRect(app.renderer, &rect) < 0)
    {
        printf("Failed to draw a point: %s\n", SDL_GetError());
        exit(1);
    }
}

void DisplayManager::setTexture(string filename, uint leftCornerX, uint leftCornerY, double angle)
{
    Sprite &s = _spriteTable.at(filename);
    SDL_Texture *texture = s.getTexture();
    SDL_Rect destinationRect = {(int)leftCornerX - _cameraOffset.getX(), (int)leftCornerY - _cameraOffset.getY(), s.getWidth(), s.getHeight()};
    if (angle == 0)
    {
        SDL_RenderCopy(app.renderer, texture, NULL, &destinationRect);
    }
    else
    {
        SDL_RenderCopyEx(app.renderer, texture, NULL, &destinationRect, angle, NULL, SDL_FLIP_NONE);
    }
}

void DisplayManager::setText(string text, Position p, int width, int height)
{
    TTF_Font *Sans = TTF_OpenFont("Sans.ttf", 12);

    SDL_Color color = {249, 217, 136, 225}; // rgba(249,217,136,255)

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), color);

    SDL_Texture *Message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = p.getX();
    Message_rect.y = p.getY();
    Message_rect.w = width;
    Message_rect.h = height;

    SDL_RenderCopy(app.renderer, Message, NULL, &Message_rect);
    TTF_CloseFont(Sans);
}
