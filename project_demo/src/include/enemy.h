#ifndef ENEMY_H
#define ENEMY_H

// #include "GameObject.h"
#include <SDL2/SDL.h>

class Enemy// : public Object
{
    int x, y, w, h;
    float fx_enemy, fy_enemy;
    
    SDL_Texture *texture;
    int frames;

    public:
        float hp;
        float speed;

        bool reached = false;

        // Constructor and Destructor
        Enemy(SDL_Texture *texture, float s = 1.f, float hp = 5.f, int x=800, int y=-1, int w=85, int h=85, int frames=1);

        SDL_Rect get_rect() { return {x, y, w, h}; }

        // Enemy running
        bool active() { return (hp > 0); }
        void handle_event(const SDL_Event &event);
        void update();
        void render_color();
        void render(SDL_Renderer *renderer);
};

#endif