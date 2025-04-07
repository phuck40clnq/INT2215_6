#ifndef ENEMY_H
#define ENEMY_H

// #include "GameObject.h"
#include <SDL2/SDL.h>

class Enemy// : public Object
{
    int x, y, w, h;
    SDL_Texture *texture;
    int frames;

    public:
        int hp;
        float speed;

        // Constructor and Destructor
        Enemy(SDL_Texture *texture, int x=800, int y=-1, int w=85, int h=85, float speed=1.f, int frames=1, int hp = 5);

        SDL_Rect get_rect() { return {x, y, w, h}; }

        // Enemy running
        bool active() { return (hp > 0); }
        void handle_event(const SDL_Event &event);
        void update();
        void render(SDL_Renderer *renderer);
};

#endif