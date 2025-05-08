#ifndef BUTTON_H
#define BUTTON_H

#include "font.h"

class Button
{
    private:
        float x, y;
        int w, h;
        const char* text;
        Font* font;
        TTF_Font* current_font;
    public:
        Button(Font* font, float x, float y, int w, int h, const char* text);
        ~Button() {}

        const char* get_text() const { return text; }
        bool is_touch(float mouse_x, float mouse_y);
        void render(SDL_Renderer *renderer, float mouse_x = -1, float mouse_y = -1, bool change_color_touch = true, int pos = 0, SDL_Color color = {255, 255, 153, 255});    // Yellow
        void set_font(const char* name) { this->current_font = font->get_font(name); }
};

#endif