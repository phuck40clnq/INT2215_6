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
    this->original_speed = this->speed;
}

void Enemy::handle_event(const SDL_Event &event)
{
    return;
}

void Enemy::update()
{
    apply_bullet_effects();
    move();
    update_displayed_hp();
    update_color();
    return;
}

void Enemy::apply_bullet_effects()
{
    if (is_boss)
        apply_effects_boss();
    else
        apply_effects_normal();
}

void Enemy::apply_effects_boss()
{
    speed = original_speed;

    // Only freeze
    if (freeze_duration.is_active())    speed = 0.f;
}

void Enemy::apply_effects_normal()
{
    // --- Speed ---
    speed = original_speed;
    if (freeze_duration.is_active() || stun_duration.is_active())
    {
        speed = 0.f;
    }
    else if (is_iced && !ice_effect_duration.is_finished())
    {
        speed = ice_speed;
    }

    // --- Poison ---
    if (is_poisoned)
    {
        if (poison_effect_duration.is_finished())
        {
            is_poisoned = false;
        }
        else if (poison_tick_delay.is_finished())
        {
            hp -= poison_damage;
            poison_tick_delay.start(1000);
        }
    }

    // --- Freeze & Ice cleanup ---
    if (is_iced && ice_effect_duration.is_finished())
    {
        is_iced = false;
    }
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
    fx_enemy -= speed;
    if (fx_enemy < 0)
    {
        reached = true;
    }
}

void Enemy::update_color()
{
    if (is_boss)
        update_boss_color();
    else
        update_normal_color();
}

void Enemy::update_boss_color()
{
    if (freeze_duration.is_active())
    {
        enemy_color = {0, 0, 255, 255}; // Frozen - Blue
        return;
    }

    float hp_ratio = hp / max_hp;
    int color_value = std::min(255, int(hp_ratio * 255));

    Uint8 red = 255;
    Uint8 green = static_cast<Uint8>(color_value);
    Uint8 blue = static_cast<Uint8>(color_value);
    enemy_color = {red, green, blue, 255};

    // Set default
    enemy_color = {255, 255, 255, 255};

    return;
}

void Enemy::update_normal_color()
{
    if (freeze_duration.is_active())
    {
        enemy_color = {0, 0, 255, 255}; // Frozen - Blue
        return;
    }

    if (stun_duration.is_active())
    {
        enemy_color = {255, 255, 0, 255}; // Stun - Yellow
        return;
    }

    if (is_poisoned)
    {
        enemy_color = {0, 200, 0, 255}; // Poison - Green
        return;
    }

    if (is_iced)
    {
        enemy_color = {100, 100, 255, 255}; // Ice slow - Soft Blue
        return;
    }

    // Set default
    enemy_color = {255, 255, 255, 255};

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