#ifndef GAME_SETTING_H
#define GAME_SETTING_H

#include "board.h"

class Game_setting
{
    Font* font;
    Board* board;
    Board* instruction;
    std::vector<Button> buttons;

    Music* music;
    SDL_Renderer* renderer;

public:
    Game_setting(Music* music, Font* font, SDL_Renderer* renderer, int x, int y, int w, int h);
    ~Game_setting() { clean(); }

    void render(bool draw_transparent = true);
    void handle_event(SDL_Event& event);
    // int get_selected_button_index(SDL_Event& event);
    void clean();
};

#endif
