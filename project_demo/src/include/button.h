#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Button
{
    private:
        int x, y, w, h;
        const char* text;
        TTF_Font* font;
    public:
        Button(int x, int y, int w, int h, const char* text);
        ~Button() { if (font != nullptr) TTF_CloseFont(font); }

        const char* get_text() const { return text; }
        bool is_touch(int mouse_x, int mouse_y);
        void render(SDL_Renderer *renderer, int mouse_x, int mouse_y);
        void set_font(TTF_Font* font) { this->font = font; }
};

#endif