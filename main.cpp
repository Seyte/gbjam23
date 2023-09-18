#include "SDL.h" /* All SDL App's need this */
#include <stdio.h>

#define SCALE_FACTOR 5
#define DEFAULT_SCREEN_WIDTH 160
#define DEFAULT_SCREEN_HEIGHT 144
#define SCREEN_WIDTH DEFAULT_SCREEN_WIDTH *SCALE_FACTOR
#define SCREEN_HEIGHT DEFAULT_SCREEN_HEIGHT *SCALE_FACTOR
#define GAME_NAME "Game"

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

    app.window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

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

void doInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                printf("keyup\n");
                break;
            case SDLK_DOWN:
                printf("keydown\n");
                break;
            case SDLK_LEFT:
                printf("keyleft\n");
                break;
            case SDLK_RIGHT:
                printf("keyright\n");
                break;
            }
            break;
        case SDL_QUIT:
            exit(0);
            break;

        default:
            break;
        }
    }
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void renderScene(void)
{
    SDL_RenderPresent(app.renderer);
}

// de-alloc all memory
void clean(void)
{
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    memset(&app, 0, sizeof(App));

    initSDL();

    atexit(clean);

    while (1)
    {
        prepareScene();

        doInput();

        renderScene();
    }

    exit(0);
}
