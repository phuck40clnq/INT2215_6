#ifndef GAME_GAMEOVER_H
#define GAME_GAMEOVER_H

#include <SDL2/SDL_image.h>
#include "board.h"
#include "Game_state.h"
#include "texture.h"

class Game_Gameover
{
    private:
        std::vector<Button> buttons;

        Board* instruction,* setting,* quit;

        SDL_Renderer* renderer;
        Music* music;
        Font* font;
        Texture* texture;

        float background_x = 0.f;
        float background_speed = 1.f;

    public:
        Game_Gameover(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting, Board* quit);
        ~Game_Gameover() { clean(); }

        void init();
        void create_buttons();
        void handle_event(SDL_Event& event);
        void handle_click(SDL_Event& event);
        void handle_button_click(Button& button);
        void handle_overlay(SDL_Event& event);
        void toggle_overlay(OVERLAY overlay, Board* board);

        void update();
        void render();
        void clean();
};

#endif