#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include "board.h"
#include "button.h"
#include <vector>

class Game_setting
{
    Board* board;
    std::vector<Button> buttons;

public:
    Game_setting(SDL_Renderer* renderer, int x, int y, int w, int h);
    ~Game_setting() { clean(); }

    void set_font(TTF_Font* font);
    void render(bool draw_transparent = true);
    void handle_event(SDL_Event& event);
    int get_selected_button_index(SDL_Event& event);
    void clean();
};

#endif
