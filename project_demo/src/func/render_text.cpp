#include "render_text.h"

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font)
{
    if (!font)  return;
    // Draw into the rect
    SDL_Color text_color = {0, 0, 0, 255};  // Black
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
    if (!text_surface)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can not create text_surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can not create text_texture: %s", TTF_GetError());
        SDL_FreeSurface(text_surface);
        return;
    }

    SDL_Rect text_rect;
    text_rect = {x, y, text_surface->w, text_surface->h};

    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}