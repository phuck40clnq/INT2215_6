#ifndef PLAYER_H
#define PLAYER_H

#include "animation.h"
#include "bullet.h"
// #include "GameObject.h"
#include "music.h"
#include "TimeDelay.h"
#include <SDL2/SDL.h>
#include <vector>

class Player// : public Object
{
    int x, y, w, h; float fx, fy;
    SDL_Texture *texture;
    int frames;
    int max_frames;
    std::vector<Bullet> bullets;
    SDL_Rect src;

    bool move_sound_playing = false;
    Music* music;

    // Buff
    float speed, bullet_speed, bullet_damage;
    float normal_speed, normal_bullet_speed, normal_bullet_damage;
    float buff_speed, buff_bullet_speed, buff_bullet_damage;
    TimeDelay buff_timer;

    // Animations
    Animation *animation;

    // For features
    Uint32 last_combo_time = 0;
    Uint32 last_combo_reset_time = 0;


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

        void update_data();
        void update_data_bullet();


        // Constructor
        Player(Music* music, SDL_Texture *texture, int x=360, int y=270, int w=80, int h=80, int frames=1);
        ~Player() { clean(); }

        SDL_Rect get_rect() { return {x, y, w, h}; }
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