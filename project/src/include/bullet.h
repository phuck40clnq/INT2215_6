#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include <unordered_set>

class Enemy;

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
    float x, y, width_bullet = 10.f, height_bullet = 10.f;
    float s;
    BULLET_TYPE type = BULLET_TYPE::DEFAULT;
    SDL_Color bullet_color = {255, 255, 255, 255}; // Default color

    std::unordered_set<Enemy*> hit_enemies;

    public:
        bool is_active;
        float damage;
        // Constructor and Destructor
        Bullet(float x, float y, float s = 5.f, float damage = 2.f, BULLET_TYPE type = BULLET_TYPE::DEFAULT);
        ~Bullet();
        void set_color_from_type();
        void set_properties_from_type();

        SDL_FRect get_rect() { return {x, y, width_bullet, height_bullet}; }

        // Getter, setter type
        BULLET_TYPE get_type() { return type; };
        void set_type(BULLET_TYPE type) { this->type = type; set_color_from_type(); set_properties_from_type(); };

        // Get bullet
        bool active() { return is_active; };
        void update();
        void render(SDL_Renderer* renderer);

        bool has_hit_enemy(Enemy* enemy);
        void mark_hit_enemy(Enemy* enemy);
};

#endif