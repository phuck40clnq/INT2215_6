#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main()
{
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Khởi tạo SDL_Image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        cout << "IMG_Init failed: " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Tạo window
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Tạo renderer
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    if (render == NULL)
    {
        cout << "SDL_CreateRenderer failed: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Tải background và nhân vật
    SDL_Texture *background = IMG_LoadTexture(render, "images/background.jpg");
    SDL_Texture *player = IMG_LoadTexture(render, "images/player.png");
    if (!background || !player)
    {
        cout << "IMG_LoadTexture failed: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect playerRect = { 400, 300, 50, 50 };

    SDL_Event event;
    bool running = true;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:    playerRect.y += 5; break;
                    case SDLK_DOWN:  playerRect.y -= 5; break;
                    case SDLK_LEFT:  playerRect.x -= 5; break;
                    case SDLK_RIGHT: playerRect.x += 5; break;
                }
            }
        }

        SDL_RenderClear(render);
        SDL_RenderCopy(render, background, NULL, NULL);
        SDL_RenderCopy(render, player, NULL, &playerRect);
        SDL_RenderPresent(render);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}