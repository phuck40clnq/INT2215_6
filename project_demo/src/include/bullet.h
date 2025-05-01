#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#define width_bullet 10
#define height_bullet 10

class Bullet
{
    float x, y;
    float s;
    public:
        bool is_active;
        float damage;
        // Constructor and Destructor
        Bullet(float x, float y, float s = 5.f, float damage = 2.f);
        ~Bullet();

        SDL_FRect get_rect() { return {x, y, float(width_bullet), float(height_bullet)}; }

        // Get bullet
        bool active() { return is_active; };
        void update();
        void render(SDL_Renderer* renderer);
};

#endif