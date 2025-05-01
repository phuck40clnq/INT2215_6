#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SDL2/SDL_image.h>
#include "board.h"
#include "Game_state.h"
#include "texture.h"


class Game_Menu
{
    private:
        std::vector<Button> buttons;

        Board* instruction,* setting;

        SDL_Renderer* renderer;
        Music* music;
        Font* font;
        Texture* texture;

    public:
        Game_Menu(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting);
        ~Game_Menu() { clean(); }

        void init();
        void create_buttons();
        void handle_event(SDL_Event& event);
        void handle_click(SDL_Event& event);
        void handle_button_click(Button& button);
        void handle_overlay(SDL_Event& event);
        void toggle_overlay(OVERLAY overlay, Board* board);

        void render();
        void clean();
};

#endif