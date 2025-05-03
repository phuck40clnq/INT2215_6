#include "../include/bullet.h"

Bullet::Bullet(float x, float y, float s, float damage, BULLET_TYPE type)
    : x(x), y(y), s(s), damage(damage), is_active(true), type(type)
{
    set_color_from_type();
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

void Bullet::render(SDL_Renderer* renderer)
{
    if (!is_active) return;
    SDL_FRect rect = {x, y, float(width_bullet), float(height_bullet)};
    SDL_SetRenderDrawColor(renderer, bullet_color.r, bullet_color.g, bullet_color.b, bullet_color.a);
    SDL_RenderFillRectF(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Reset to black
}