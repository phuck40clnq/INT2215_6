#include "../include/enemy.h"
#include "../func/render.h"
#include <random>
#include <algorithm>

Enemy::Enemy(Music* music, SDL_Texture *texture, float s, float hp, int x, int y, int w, int h, bool is_boss, int frames)
    // : Object(texture, x, y, w, h), speed(speed), frames(frames), max_frames(max_frames), hp(hp) 
    : texture(texture), max_hp(hp), x(x), y(y), w(w), h(h), is_boss(is_boss), frames(frames)
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_normal(0, 5);
    std::uniform_int_distribution<> dist_bigboss(0, 2);
    
    // Normal enemy
    if (y == -1 && !is_boss)        this->y = dist_normal(gen) * 86 + 80;

    // Boss
    else if (y == -1 && is_boss)    this->y = dist_bigboss(gen) * 172 + 80;

    this->hp = this->max_hp;
    this->displayed_hp = this->hp;
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
    move();
    update_displayed_hp();
    return;
}

void Enemy::update_displayed_hp()
{
    if (displayed_hp > hp)
    {
        float delta = 0.5f;  // Tốc độ giảm (có thể điều chỉnh nhanh/chậm)
        displayed_hp -= delta;
        if (displayed_hp < hp) displayed_hp = hp;
    }
}

void Enemy::move()
{
    if (move_delay.is_active())
    {
        return;
    }
    fx_enemy -= speed;
    if (fx_enemy < 0)
    {
        reached = true;
    }
    x = int (fx_enemy);
    y = int (fy_enemy);
}

void Enemy::render_color()
{
    int color_value = std::min(255, int(hp * 10));
    SDL_SetTextureColorMod(texture, 255, color_value, color_value);
    return;
}

void Enemy::render(SDL_Renderer *renderer)
{
    // Object::render(renderer);
    render_color();
    SDL_Rect dst = {x, y, w, h};
    if (hit_delay.is_active())  SDL_SetTextureColorMod(texture, 255, 100, 100); // Change color
    else                        SDL_SetTextureColorMod(texture, 255, 255, 255); // Reset color
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    // Render HP bar
    if (is_boss)
        render_hp(renderer, displayed_hp, max_hp, x, y, w, h, true);
    else
        render_hp(renderer, displayed_hp, max_hp, x, y, w, h);

    return;
}