#include "player.h"

// Constructor
Player::Player(SDL_Renderer *renderer, char* imagePath, int _x, int _y)
{
    player = IMG_LoadTexture(renderer, imagePath);
    if (!player)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture player failed: %s", IMG_GetError());
        return;
    }
}

// Destructor
Player::~Player()
{
    SDL_DestroyTexture(player);
}