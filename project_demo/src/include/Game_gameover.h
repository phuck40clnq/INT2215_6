#ifndef GAME_GAMEOVER_H
#define GAME_GAMEOVER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "button.h"
#include "../include/music.h"

class Game_Gameover
{
    private:
        TTF_Font* font;
        SDL_Texture* texture;
        Music music;
        std::vector<Button> buttons;

    public:
        Game_Gameover(SDL_Renderer* renderer) { init(renderer); create_buttons(); this->texture = nullptr; this->font = nullptr; }
        ~Game_Gameover() { clean(); }

        void init(SDL_Renderer* renderer);
        void create_buttons();
        void handle_event();
        void render(SDL_Renderer* renderer);
        void clean();
};

#endif