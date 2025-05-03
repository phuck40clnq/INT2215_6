#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <vector>

#include "button.h"
#include "music.h"
#include "render.h"

class Board
{
    bool active;
    SDL_Rect rect, text_rect;

    std::vector<const char*> lines;
    SDL_Color text_color;
    SDL_Renderer* renderer;
    Button close_button;

    std::vector<Button> extra_buttons; // Thêm vector này

    // Thông số sắp xếp các button
    float button_x_offset = 10;
    float button_y_offset = 10;
    float button_spacing = 5;
    int button_count = 0;

    void draw_transparent();

    Music* music;
    Font* font;
    const char* name_font;

    public:
        Board(Music* music, Font* font, SDL_Renderer* renderer, int x, int y, int w, int h);
        ~Board() { clean(); }
        
        void set_active(bool active) { this->active = active; }
        bool is_active() { return active; }
        void set_text(std::vector<const char*> line, SDL_Color text_color={255, 255, 255, 255});
        void set_font(const char* name);
        void handle_event(SDL_Event& event);
        void render(bool draw_transparent = false, SDL_Color color = {0, 0, 0, 255});
        void clean();

        void add_button(const char* text);
};

#endif