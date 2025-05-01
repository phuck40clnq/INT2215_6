#include "../include/enemy.h"
#include "../include/render.h"
#include <random>
#include <algorithm>

Enemy::Enemy(Music* music, Texture* texture, const char* texture_name, float s, float hp, float x, float y, int w, int h, bool is_boss, int frames)
    // : Object(texture, x, y, w, h), speed(speed), frames(frames), max_frames(max_frames), hp(hp) 
    : texture(texture), texture_enemy_name(texture_name), speed(s), max_hp(hp), fx_enemy(x), fy_enemy(y), w(w), h(h), is_boss(is_boss), frames(frames)
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_normal(0, 5);
    std::uniform_int_distribution<> dist_bigboss(0, 2);
    
    // Normal enemy
    if (fy_enemy == -1.f && !is_boss)        this->fy_enemy = dist_normal(gen) * 86 + 80;

    // Boss
    else if (fy_enemy == -1.f && is_boss)    this->fy_enemy = dist_bigboss(gen) * 172 + 80;

    this->hp = this->max_hp;
    this->displayed_hp = this->hp;
}

void Enemy::handle_event(const SDL_Event &event)
{
    return;
}

void Enemy::update()
{
    move();
    update_displayed_hp();
    update_color();
    return;
}

void Enemy::update_displayed_hp()
{
    if (displayed_hp > hp)
    {
        float delta = 0.5f; // Decrease displayed HP
        displayed_hp -= delta;
        if (displayed_hp < hp) displayed_hp = hp;
    }
}

void Enemy::move()
{
    // Normal enemy has delay
    if (move_delay.is_active() && !is_boss)
    {
        return;
    }
    fx_enemy -= speed;
    if (fx_enemy < 0)
    {
        reached = true;
    }
}

void Enemy::update_color()
{
    if (hit_delay.is_active())
    {
        enemy_color = {255, 100, 100, 255}; // Change color
        return;
    }

    if (!is_boss)
    {
        enemy_color = {255, 255, 255, 255}; // Normal enemy
        return;
    }

    float hp_ratio = hp / max_hp;
    int color_value = std::min(255, int(hp_ratio * 255));

    Uint8 red = 255;
    Uint8 green = static_cast<Uint8>(color_value);
    Uint8 blue = static_cast<Uint8>(color_value);
    enemy_color = {red, green, blue, 255}; // Boss enemy

    return;
}

void Enemy::render(SDL_Renderer *renderer)
{
    // Object::render(renderer);
    SDL_Color color = enemy_color;
    SDL_FRect dst = {fx_enemy, fy_enemy, float(w), float(h)};
    texture->render(texture_enemy_name, dst, color);

    // Render HP bar
    // if (is_boss)
        render_hp(renderer, displayed_hp, max_hp, fx_enemy, fy_enemy, w, h, true);

    return;
}