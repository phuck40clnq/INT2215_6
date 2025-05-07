#include "../include/item.h"
#include "../include/Game_playing.h"

#include <random>

Item::Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated, bool repeat)
    : effect(effect), trigger(trigger), delay(delay), level(level), enemy_count(enemy_count), boss_defeated(boss_defeated), repeat(repeat)
{
    this->rect = { x, y, w, h };

    // Check if random
    if (x == -1.f && y == -1.f)
    {
        random_position();
    }
    this->texture = texture;
    this->texture_name = texture_name;
    this->is_active = false;
}

void Item::render(SDL_Renderer* renderer)
{
    texture->render(texture_name, rect);
}

void Item::clean()
{
    return;
}

void Item::ready(const Game_Playing& game)
{
    switch (trigger)
    {
        case ITEM_TRIGGER::TIME_BASED:
            if (!is_time_started)  
            {
                timer.start(delay);
                is_time_started = true;
                SDL_Log("Timer started with delay: %d", delay);
            }
            else
            {
                if (timer.is_finished())
                {
                    SDL_Log(">>> Item is ready!");
                    set_active(true);
                }
            }
            break;

        case ITEM_TRIGGER::PLAYER_LEVEL:
            if (game.player->player_level >= level)
                set_active(true);
            break;

        case ITEM_TRIGGER::ENEMY_COUNT:
            if (game.current_enemy >= enemy_count)
                set_active(true);
            break;

        case ITEM_TRIGGER::BOSS_DEFEATED:
            if (game.count_boss_defeated >= boss_defeated)
                set_active(true);
            break;
        case ITEM_TRIGGER::NONE:
            break;
        default:
            break;
    }
}

void Item::random_position()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist_x(0.f, 800.f - int(rect.w));
    std::uniform_real_distribution<float> dist_y(80.f, 600.f - int(rect.h));
    rect.x = dist_x(gen);
    rect.y = dist_y(gen);
}

void Item::set_active(bool active)
{
    is_active = active;

    if (!repeat)    return;

    // Repeat
    if (active)    return;
    random_position();
    switch (trigger)
    {
        case ITEM_TRIGGER::TIME_BASED:
            is_time_started = false;
            break;

        case ITEM_TRIGGER::PLAYER_LEVEL:
            level += 3;
            break;

        case ITEM_TRIGGER::ENEMY_COUNT:
            enemy_count += 2;
            break;

        case ITEM_TRIGGER::BOSS_DEFEATED:
            boss_defeated++;
            break;
        case ITEM_TRIGGER::NONE:
            break;
        default:
            break;
    }
}
