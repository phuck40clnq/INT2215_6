#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, int angle = 0, SDL_Color color = {0, 0, 0, 255});

void render_hp(SDL_Renderer* renderer, float hp, float max_hp, int x, int y, int w, int h, bool change_color = false);

#endif