#ifndef GAME_PLAYING_H
#define GAME_PLAYING_H

#include "board.h"
#include "button.h"
#include "enemy.h"
#include "Game_state.h"
#include "item.h"
#include "player.h"
#include "texture.h"

// Max number of enemies
#define max_enemies 12
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
        std::vector<Enemy*> enemies_to_delete;  std::vector<Enemy*> enemies_to_add;

        int count_boss_defeated = 0;

        void update_num_enemy()
        {
             // Delete enemies
            for (auto& delete_enemy : enemies_to_delete)   delete delete_enemy;
            enemies_to_delete.clear();

            // Add enemies
            for (auto& add_enemy : enemies_to_add)  enemies.push_back(add_enemy);
            enemies_to_add.clear();
        }

        std::vector<Item*> items;

        SDL_Renderer* renderer;
        Music* music;
        Font* font;
        Texture* texture;

        Game_Playing(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting);
        ~Game_Playing() { clean(); }

        void create_buttons();
        void init();
        void handle_event(SDL_Event& event);
        void handle_click(SDL_Event& event);
        void handle_button_click(Button& button);
        void handle_overlay(SDL_Event& event);
        void toggle_overlay(OVERLAY overlay, Board* board);
        void update();
        void render();
        void render_for_buttons(int score, int time_seconds);
        void clean();
};

#endif