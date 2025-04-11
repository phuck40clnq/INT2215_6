#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void render_text(SDL_Renderer* renderer, const char* text, int x, int y, TTF_Font* font, int angle = 0);

#endif