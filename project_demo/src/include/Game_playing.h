#ifndef GAME_PLAYING_H
#define GAME_PLAYING_H

#include "board.h"
#include "button.h"
#include "enemy.h"
#include "Game_state.h"
#include "all_items.h"
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

    std::vector<Item*> items;

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

        void clean_enemy()
        {
             // Delete enemies
            for (auto& delete_enemy : enemies_to_delete)   delete delete_enemy;
            enemies_to_delete.clear();

            // Add enemies
            for (auto& add_enemy : enemies_to_add)  enemies.push_back(add_enemy);
            enemies_to_add.clear();
        }

        SDL_Renderer* renderer;
        Music* music;
        Font* font;
        Texture* texture;

        // Items
        std::vector<Item*> items_to_delete;
        std::vector<Item*>& get_items() { return items; }
        void add_item_to_game(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay = -1, int level = -1, int enemy_count = -1, int boss_defeated = -1);
        void add_all_items_to_game();
        void update_items();
        void render_items();
        void clean_items()
        {
            for (auto item : items_to_delete)
            {
                auto it = std::find(items.begin(), items.end(), item);
                if (it != items.end())
                {
                    delete *it;
                    items.erase(it);
                }
            }
            items_to_delete.clear();
        }

        Game_Playing(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting);
        ~Game_Playing() { clean(); }

        void create_buttons();
        void init();
        void loadtexture_item();
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