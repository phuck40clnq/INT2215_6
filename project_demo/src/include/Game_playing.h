#ifndef GAME_PLAYING_H
#define GAME_PLAYING_H

#include "button.h"
#include "enemy.h"
#include "player.h"
#include "Game_state.h"

class Game_Playing
{
    TTF_Font* font;
    std::vector<Button> buttons;
    Music music;
    SDL_Texture *background;

    public:
        Player *player; SDL_Texture *player_texture;
        std::vector<Enemy*> enemies; SDL_Texture *enemy_texture;

        Game_Playing(SDL_Renderer* renderer) { init(renderer); create_buttons(); this->background = nullptr; this->font = nullptr; }
        ~Game_Playing() { clean(); }

        void create_buttons();
        void init(SDL_Renderer* renderer);
        // bool init(SDL_Renderer* renderer);
        void handle_event();
        void update();
        void render(SDL_Renderer* renderer);
        void clean();
};

#endif