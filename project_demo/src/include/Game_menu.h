#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "button.h"
#include "music.h"

class Game_Menu
{
    private:
        TTF_Font* font, *welcome_font;
        SDL_Texture* texture;
        std::vector<Button> buttons;
        Music music;

    public:
        Game_Menu(SDL_Renderer* renderer) { init(renderer); create_buttons(); }
        ~Game_Menu() { clean(); }

        void init(SDL_Renderer* renderer);
        void create_buttons();
        void handle_event();
        void render(SDL_Renderer* renderer);
        void clean();
};

#endif