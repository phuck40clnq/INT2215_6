#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <vector>

#include "button.h"

#include "../func/render.h"

class Board
{
    bool active;
    SDL_Rect rect, text_rect;
    TTF_Font* font;
    std::vector<const char*> lines;
    SDL_Color text_color;
    SDL_Renderer* renderer;
    Button close_button;
    void draw_transparent();

    public:
        Board(SDL_Renderer* renderer, int x, int y, int w, int h, int key);
        ~Board() { clean(); }

        SDL_Renderer* get_renderer() const { return renderer; }
        
        void set_active(bool active) { this->active = active; }
        bool is_active() const { return active; }
        void set_text(std::vector<const char*> line, SDL_Color color={255, 255, 255, 255});
        void handle_event();
        void render(bool draw_transparent = false);
        void clean();
};

#endif