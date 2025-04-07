#include "../include/enemy.h"
#include <random>

Enemy::Enemy(SDL_Texture *texture, int x, int y, int w, int h, float speed, int frames, int hp)
    // : Object(texture, x, y, w, h), speed(speed), frames(frames), max_frames(max_frames), hp(hp) 
    : texture(texture), x(x), y(y), w(w), h(h), frames(frames), hp(hp)
{
    if (y == -1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 5);
        this->y = dist(gen) * 100;
    }
}

void Enemy::handle_event(const SDL_Event &event)
{
    return;
}

void Enemy::update()
{
    x -= speed;
    if (x < 0)
    {
        x = 800;
    }
    return;
}

void Enemy::render(SDL_Renderer *renderer)
{
    // Object::render(renderer);
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    return;
}