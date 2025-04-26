#ifndef GAME_GAMEOVER_H
#define GAME_GAMEOVER_H

#include <SDL2/SDL_image.h>
#include "board.h"

class Game_Gameover
{
    private:
        SDL_Texture* texture;
        std::vector<Button> buttons;

        Board* instruction,* setting;

        SDL_Renderer* renderer;
        Music* music;
        Font* font;

    public:
        Game_Gameover(SDL_Renderer* renderer, Music* music, Font* font, Board* instruction, Board* setting);
        ~Game_Gameover() { clean(); }

        void init();
        void create_buttons();
        void handle_event(SDL_Event& event);
        void handle_button_click(Button& button);
        void render();
        void clean();
};

#endif