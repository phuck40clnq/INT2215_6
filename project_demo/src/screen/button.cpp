#include "../include/button.h"

Button::Button(Font* font, int x, int y, int w, int h, const char* text)
    : font(font), x(x), y(y), w(w), h(h), text(text) {}

bool Button::is_touch(int mouse_x, int mouse_y)
{
    return mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h;
}

void Button::render(SDL_Renderer *renderer, int mouse_x, int mouse_y, bool change_color_touch, int pos, SDL_Color color)
{
    SDL_Rect button_rect = {x, y, w, h};
    if (change_color_touch)     // Button change color
    {
        if (is_touch(mouse_x, mouse_y))
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);    // Green button
        else
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);    // Red button
    }
    else
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);    // Custom color

    SDL_RenderFillRect(renderer, &button_rect);

    if (!current_font)  return;
    // Draw into the rect
    SDL_Color text_color = {0, 0, 0, 255};  // Black
    SDL_Surface* text_surface = TTF_RenderText_Solid(current_font, text, text_color);
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
    if (pos == 0)        text_rect = {x + (w - text_surface->w) / 2, y + (h - text_surface->h) / 2 + 5, text_surface->w, text_surface->h};
    else if (pos == -1)  text_rect = {x + 5, y + (h - text_surface->h) / 2 + 5, text_surface->w, text_surface->h};
    else if (pos == 1)   text_rect = {x + (w - text_surface->w) - 5, y + (h - text_surface->h) / 2 + 5, text_surface->w, text_surface->h};


    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}