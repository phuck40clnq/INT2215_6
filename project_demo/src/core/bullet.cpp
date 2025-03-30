#include "bullet.h"

Bullet::Bullet(int x, int y, int s)
    : x(x), y(y), s(s), is_active(true) {}

Bullet::~Bullet() {}

void Bullet::update()
{
    x += speed;
    if (x > 800)
    {
        is_active = false;
    }
    return;
}

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {x, y, width_bullet, height_bullet};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}