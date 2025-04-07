#ifndef GAME_PLAYING_H
#define GAME_PLAYING_H

#include "button.h"
#include "enemy.h"
#include "player.h"
#include "Game_state.h"

// Max number of enemies
#define max_enemies 20
#define ENEMY 6

class Game_Playing
{
    TTF_Font* font1, *font2;
    std::vector<Button> buttons;
    Music music;
    SDL_Texture *background;

    int time_seconds = 0;
    unsigned last_time = 0;

    public:
        int score = 0;
        Player *player; SDL_Texture *player_texture;
        std::vector<Enemy*> enemies; SDL_Texture *enemy_texture; int current_enemy = ENEMY;

        Game_Playing(SDL_Renderer* renderer) { init(renderer); create_buttons(); }
        ~Game_Playing() { clean(); }

        void create_buttons();
        void init(SDL_Renderer* renderer);
        void handle_event();
        void update();
        void render(SDL_Renderer* renderer);
        void render_for_buttons(SDL_Renderer* renderer, int score, int time_seconds);
        void clean();
};

#endif