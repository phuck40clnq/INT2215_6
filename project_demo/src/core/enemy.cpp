#include "enemy.h"

Enemy::Enemy(SDL_Texture *texture, int x, int y, int w, int h, int speed, int frames, int max_frames, int hp)
    : Object(texture, x, y, w, h), speed(speed), frames(frames), max_frames(max_frames), hp(hp) {}

void Enemy::handle_event(const SDL_Event &event)
{
    return;
}

void Enemy::update()
{
    x -= 1;
    if (x < 0)
    {
        x = 800;
    }
    return;
}

void Enemy::render(SDL_Renderer *renderer)
{
    Object::render(renderer);
    return;
}