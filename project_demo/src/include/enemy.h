#ifndef ENEMY_H
#define ENEMY_H

// #include "GameObject.h"
#include <SDL2/SDL.h>
#include "../include/music.h"
#include "../include/TimeDelay.h"

class Enemy// : public Object
{
    int x, y, w, h;
    float fx_enemy, fy_enemy;
    
    SDL_Texture *texture;
    int frames;

    Music* music;

    public:
        float hp, max_hp, displayed_hp;
        float speed;

        bool reached = false;
        bool is_boss;

        TimeDelay hit_delay;
        TimeDelay move_delay;

        // Constructor and Destructor
        Enemy(Music* music, SDL_Texture *texture, float s = 1.f, float hp = 5.f, int x=800, int y=-1, int w=85, int h=85, bool is_boss=false, int frames=1);

        SDL_Rect get_rect() { return {x, y, w, h}; }

        // Enemy running
        bool active() { return (hp > 0); }
        void handle_event(const SDL_Event &event);
        void update();
        void move();
        void update_displayed_hp();
        void render_color();
        void render(SDL_Renderer *renderer);
};

#endif