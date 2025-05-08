#ifndef ENEMY_H
#define ENEMY_H

// #include "GameObject.h"
#include <SDL2/SDL.h>
#include "music.h"
#include "texture.h"
#include "TimeDelay.h"

class Enemy// : public Object
{
    int w, h;
    float fx_enemy, fy_enemy;
    
    int frames;

    Music* music;
    Texture *texture;
    const char* texture_enemy_name;

    // Color
    SDL_Color enemy_color = {255, 255, 255, 255}; // White

    public:
        float hp, max_hp, displayed_hp;
        float speed, original_speed;

        bool reached = false;
        bool is_boss;

        // Bullet_type
        TimeDelay freeze_duration, ice_effect_duration, 
        poison_tick_delay, poison_effect_duration, 
        stun_duration;
        bool is_iced = false, is_frozen = false, is_poisoned = false, is_stun = false;
        float ice_speed, poison_damage;

        // Constructor and Destructor
        Enemy(Music* music, Texture* texture, const char* texture_name, float s = 1.f, float hp = 5.f, float x=850.f, float y=-1.f, int w=85, int h=85, bool is_boss=false, int frames=1);

        SDL_FRect get_rect() { return {fx_enemy, fy_enemy, float(w), float(h)}; }

        // Enemy running
        bool active() { return (hp > 0); }
        void handle_event(const SDL_Event &event);
        void update();
        void apply_bullet_effects();
        void apply_effects_boss();
        void apply_effects_normal();
        void update_color();
        void update_boss_color();
        void update_normal_color();
        void move();
        void update_displayed_hp();
        void render(SDL_Renderer *renderer);


        SDL_Color get_color() { return enemy_color; }
        void set_color(SDL_Color color) { enemy_color = color; }
};

#endif