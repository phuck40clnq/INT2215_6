#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#define width_bullet 10
#define height_bullet 10
#define speed 5

class Bullet
{
    int x, y;
    int s;
    public:
        bool is_active;

        // Constructor and Destructor
        Bullet(int x, int y, int s);
        ~Bullet();

        SDL_Rect get_rect() { return {x, y, width_bullet, height_bullet}; }

        // Get bullet
        bool active() { return is_active; };
        void erase();
        void update();
        void render(SDL_Renderer* renderer);
};

#endif