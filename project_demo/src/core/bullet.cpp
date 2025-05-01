#include "../include/bullet.h"

Bullet::Bullet(float x, float y, float s, float damage)
    : x(x), y(y), s(s), damage(damage), is_active(true) 
    {}

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

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_FRect rect = {x, y, float(width_bullet), float(height_bullet)};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(renderer, &rect);
}