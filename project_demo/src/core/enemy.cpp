#include "../include/enemy.h"
#include <random>
#include <algorithm>

Enemy::Enemy(SDL_Texture *texture, float s, float hp, int x, int y, int w, int h, int frames)
    // : Object(texture, x, y, w, h), speed(speed), frames(frames), max_frames(max_frames), hp(hp) 
    : texture(texture), hp(hp), x(x), y(y), w(w), h(h), frames(frames)
{
    if (y == -1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 5);
        this->y = dist(gen) * 85 + 80;
    }

    this->speed = s;
    this->fx_enemy = this->x;
    this->fy_enemy = this->y;
}

void Enemy::handle_event(const SDL_Event &event)
{
    return;
}

void Enemy::update()
{
    fx_enemy -= speed;
    if (fx_enemy < 400)
    {
        reached = true;
    }
    x = int (fx_enemy);
    y = int (fy_enemy);
    return;
}

void Enemy::render_color()
{
    int color_value = std::max(0, int(hp * 10));
    SDL_SetTextureColorMod(texture, 255, color_value, color_value);
    return;
}

void Enemy::render(SDL_Renderer *renderer)
{
    // Object::render(renderer);
    render_color();
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    return;
}