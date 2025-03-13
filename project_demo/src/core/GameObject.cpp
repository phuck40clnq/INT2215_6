#include "GameObject.h"

// Constructor
Object::Object(int x, int y, int w, int h) 
    : x(x), y(y), w(w), h(h), texture(NULL) {}

// Destructor
Object::~Object()
{
    SDL_DestroyTexture(texture);
}

bool Object::LoadTexture(SDL_Renderer *renderer, const char* imagePath)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(renderer, imagePath);
    
    if (!texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture failed %s: %s", imagePath, IMG_GetError());
        return false;
    }

    return true;
}

void Object::render(SDL_Renderer *renderer)
{
    SDL_Rect dst = {x, y, w, h};

    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);
}