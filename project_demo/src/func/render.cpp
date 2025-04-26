#include "render.h"

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, int angle, SDL_Color color)
{
    if (!font)  return;
    // Draw into the rect
    // SDL_Color text_color = {0, 0, 0, 255};  // Black
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
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

    if (angle == 0)
        SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

    else
        SDL_RenderCopyEx(renderer, text_texture, nullptr, &text_rect, angle, nullptr, SDL_FLIP_NONE);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void render_hp(SDL_Renderer* renderer, float hp, float max_hp, int x, int y, int w, int h, bool change_color)
{
    int bar_width = 50;
    int bar_height = 5;

    float ratio = float(hp) / max_hp;
    int hp_width = int (ratio * bar_width + 0.5f);
    int hp_bar_x = x + w / 2 - bar_width / 2;
    int hp_bar_y = y + h - 5;

    SDL_Rect hp_bar = {hp_bar_x, hp_bar_y, hp_width, bar_height};

    if (change_color)
    {
        if (hp > max_hp * 0.5)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
        else if (hp > max_hp * 0.25)
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
        else
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    }
    else
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green

    // Draw
    SDL_RenderFillRect(renderer, &hp_bar);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black border
    SDL_RenderDrawRect(renderer, &hp_bar);
}