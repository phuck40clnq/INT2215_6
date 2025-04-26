#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SDL2/SDL_image.h>
#include "board.h"


class Game_Menu
{
    private:
        Font* font;
        SDL_Texture* texture;
        std::vector<Button> buttons;
        Music* music;
        Board* instruction,* setting;

        SDL_Renderer* renderer;

    public:
        Game_Menu(SDL_Renderer* renderer, Music* music, Font* font, Board* instruction, Board* setting);
        ~Game_Menu() { clean(); }

        void init();
        void create_buttons();
        void handle_event(SDL_Event& event);
        void handle_button_click(Button& button);
        void render();
        void clean();
};

#endif