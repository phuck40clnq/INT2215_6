#ifndef GAME_PLAYING_H
#define GAME_PLAYING_H

#include "board.h"
#include "button.h"
#include "enemy.h"
#include "player.h"
#include "Game_state.h"

// Max number of enemies
#define max_enemies 20
#define ENEMY 6

class Game_Playing
{
    std::vector<Button> buttons;
    SDL_Texture* background;

    int time_seconds = 0;
    unsigned last_time = 0;
    TimeDelay time_delay;

    Board* instruction,* setting;

    public:
        // Features
        // For player
        int score = 0;

        // For enemy
        float enemy_speed = 1.f;
        float enemy_hp = 5.f;

        float enemy_bigboss_speed = 0.3f;
        float enemy_bigboss_hp = 20.f;

        TimeDelay time_delay_enemy;
        Player* player; SDL_Texture* player_texture;
        std::vector<Enemy*> enemies; SDL_Texture* enemy_texture; int current_enemy = ENEMY;

        SDL_Renderer* renderer;
        Music* music;
        Font* font;

        Game_Playing(SDL_Renderer* renderer, Music* music, Font* font, Board* instruction, Board* setting);
        ~Game_Playing() { clean(); }

        void create_buttons();
        void init();
        void handle_event(SDL_Event& event);
        void update();
        void render();
        void render_for_buttons(int score, int time_seconds);
        void clean();
};

#endif