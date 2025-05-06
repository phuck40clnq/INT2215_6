#include "../include/bullet.h"
#include "../include/enemy.h"

Bullet::Bullet(float x, float y, float s, float damage, BULLET_TYPE type)
    : x(x), y(y), s(s), damage(damage), is_active(true), type(type)
{
    set_color_from_type();
    set_properties_from_type();
}

Bullet::~Bullet() {}

void Bullet::update()
{
    x += s;
    if (x > 800)
    {
        is_active = false;
    }
    return;
}

void Bullet::set_color_from_type()
{
    // Set the color based on the bullet type
    switch (type)
    {
        case BULLET_TYPE::DEFAULT:
            bullet_color = {255, 255, 255, 255}; // White
            break;
        case BULLET_TYPE::EXPLOSION:
            bullet_color = {255, 0, 0, 255}; // Red
            break;
        case BULLET_TYPE::ICE:
            bullet_color = {0, 0, 255, 255}; // Blue
            break;
        case BULLET_TYPE::POISON:
            bullet_color = {0, 255, 0, 255}; // Green
            break;
        case BULLET_TYPE::ELECTRIC:
            bullet_color = {255, 255, 0, 255}; // Yellow
            break;
    }
}

void Bullet::set_properties_from_type()
{
    switch (type)
    {
        case BULLET_TYPE::EXPLOSION:
            damage *= 2.f;
            width_bullet = 15;
            height_bullet = 15;
            break;
        case BULLET_TYPE::ICE:
            damage *= 1.f;
            break;
        case BULLET_TYPE::POISON:
            damage *= 1.f;
            break;
        case BULLET_TYPE::ELECTRIC:
            damage *= 1.2f;
            s *= 0.6f;
            break;
        default:
            break;
    }
}

void Bullet::render(SDL_Renderer* renderer)
{
    if (!is_active) return;
    SDL_FRect rect = {x, y, width_bullet, height_bullet};
    SDL_SetRenderDrawColor(renderer, bullet_color.r, bullet_color.g, bullet_color.b, bullet_color.a);
    SDL_RenderFillRectF(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Reset to black
}

bool Bullet::has_hit_enemy(Enemy* enemy)
{
    return hit_enemies.find(enemy) != hit_enemies.end();
}

void Bullet::mark_hit_enemy(Enemy* enemy)
{
    hit_enemies.insert(enemy);
}