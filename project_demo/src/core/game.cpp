#include "game.h"

// Initialize
bool Game::init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_Init failed: %s", IMG_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    // For player
    if (!player->LoadTexture(renderer, "../images/player.png"))
    {
        return false;
    }

    // Success
    isRunning = true;
    SDL_Log("Game khởi động thành công!");
    return true;
}

// Running game
void handle_key_event(SDL_Event &event)
{
    /* switch(event.key.keysym.sym)
    {
        case SDL_KEYUP: 
    } */
   return;
}
void Game::handle_event()
{
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isRunning = false;

            if (event.type == SDL_KEYDOWN)
            {
                isRunning = false;
            }

            
        }
        player->update();
        SDL_RenderClear(renderer);

        player->render(renderer);
        SDL_Delay(1000);
    }
}

void Game::update_game()
{
    player->update();
    return;
}

void Game::render()
{
    SDL_RenderPresent(renderer);
    return;
}

// Clean game
void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete player;
    return;
}

Game::~Game()
{
    clean();
}