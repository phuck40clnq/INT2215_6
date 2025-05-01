#include "../include/item.h"
#include "../include/Game_playing.h"

Item::Item(Texture* texture, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated)
    : effect(effect), trigger(trigger), delay(delay), level(level), enemy_count(enemy_count), boss_defeated(boss_defeated)
{
    this->rect = { x, y, w, h };
    this->texture = texture;
    this->is_active = false;
}

void Item::render(SDL_Renderer* renderer)
{
    texture->render(name_texture, rect, { 255, 255, 255, 255 }, false, false);
}

void Item::clean()
{
    return;
}

bool Item::is_ready(const Game_Playing& game)
{
    if (!is_active) return false;
    if (trigger == ITEM_TRIGGER::TIME_BASED)
    {
        return timer.is_finished();
    }
    if (trigger == ITEM_TRIGGER::PLAYER_LEVEL)
    {
        return game.player->player_level >= level;
    }
    if (trigger == ITEM_TRIGGER::ENEMY_KILL_COUNT)
    {
        return game.current_enemy >= enemy_count;
    }
    if (trigger == ITEM_TRIGGER::BOSS_DEFEATED)
    {
        return game.count_boss_defeated >= boss_defeated;
    }
    return false;
}