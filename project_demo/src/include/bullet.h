#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#define width_bullet 10
#define height_bullet 10

enum class BULLET_TYPE
{
    DEFAULT,
    EXPLOSION,
    ICE,
    POISON,
    ELECTRIC,
};

class Bullet
{
    float x, y;
    float s;
    BULLET_TYPE type = BULLET_TYPE::DEFAULT;
    SDL_Color bullet_color = {255, 255, 255, 255}; // Default color
    public:
        bool is_active;
        float damage;
        // Constructor and Destructor
        Bullet(float x, float y, float s = 5.f, float damage = 2.f, BULLET_TYPE type = BULLET_TYPE::DEFAULT);
        ~Bullet();
        void set_color_from_type();

        SDL_FRect get_rect() { return {x, y, float(width_bullet), float(height_bullet)}; }

        // Getter, setter type
        BULLET_TYPE get_type() { return type; };
        void set_type(BULLET_TYPE type) { this->type = type; };

        // Get bullet
        bool active() { return is_active; };
        void update();
        void render(SDL_Renderer* renderer);
};

#endif