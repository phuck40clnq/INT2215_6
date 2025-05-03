#ifndef PLAYER_H
#define PLAYER_H

#include "animation.h"
#include "bullet.h"
// #include "GameObject.h"
#include "music.h"
#include "texture.h"
#include "TimeDelay.h"
#include <SDL2/SDL.h>
#include <vector>

class Player// : public Object
{
    int w, h; float fx, fy;
    int frames;
    int max_frames;
    std::vector<Bullet> bullets;
    SDL_Rect src;

    bool move_sound_playing = false;

    Music* music;
    Texture* texture;
    const char* texture_player_name; 

    // Buff
    float player_speed, bullet_speed, bullet_damage;
    float buff_player_speed, buff_bullet_speed, buff_bullet_damage;
    float base_player_speed, base_bullet_speed, base_bullet_damage;
    float increase_player_speed=0, increase_bullet_speed=0, increase_bullet_damage=0;

    TimeDelay buff_timer, shield_timer;
    bool is_shield_active = false;

    // Animations
    Animation *animation;

    // For features
    Uint32 last_combo_time = 0;
    Uint32 last_combo_reset_time = 0;

    // Change color
    SDL_Color player_color = {255, 255, 255, 255};

    // Bullet_Item
    BULLET_TYPE current_bullet_type = BULLET_TYPE::DEFAULT;

    public:
        // Player level
        int player_level = 1;
        int player_exp = 0;
        int exp_next_level = 10;
        int next_upgrade = 3;

        bool buff = false;
        int combo_kill_count = 0;
        void buff_player(int sec, Uint32 current_time);
        void combo();

        // In buff
        void update_data_buff_combo();

        // End buff
        void reset_data();

        // Normal
        void update_data();

        // -----Item Buff-----
        // Increase base
        void increase_player_speed_buff(float speed) { increase_player_speed += speed; }
        void increase_bullet_speed_buff(float speed) { increase_bullet_speed += speed; }
        void increase_bullet_damage_buff(float damage) { increase_bullet_damage += damage; }

        // Buff shield
        bool shield_active() { return is_shield_active; }
        void buff_shield(Uint32 timer);
        void update_shield();

        // Buff exp
        void increase_player_exp(int exp) { player_exp += exp; }

        // Buff bullet type
        void set_bullet_type(BULLET_TYPE type) { current_bullet_type = type; }
        BULLET_TYPE get_bullet_type() { return current_bullet_type; }

        // -----*********-----
        // Change color
        void set_color(SDL_Color color) { player_color = color; }
        SDL_Color get_color() { return player_color; }

        // Constructor
        Player(Music* music, Texture *texture, const char* texture_name, float x=360.f, float y=270.f, int w=80, int h=80, int frames=1);
        ~Player() { clean(); }

        SDL_FRect get_rect() { return {fx, fy, float(w), float(h)}; }
        std::vector<Bullet> &get_bullets() { return bullets; }

        // Running
        void handle_event(const SDL_Event &event);
            // Hàm hỗ trợ
            void fire_bullet();   bool fired = false;
            
        void update(); //override;
            // Hàm hỗ trợ
            void move();
            bool keys[SDL_NUM_SCANCODES] = {false};
            void player_move_sound();
            void update_bullets();
        void render(SDL_Renderer *renderer); //override;
            void render_bullets(SDL_Renderer *renderer);
        void clean();
};

#endif