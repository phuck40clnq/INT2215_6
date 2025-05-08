#include "../include/boom.h"
#include "../include/Game_playing.h"

#include <random>

Boom::Boom(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated, bool repeat)
    : Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated, repeat)
{
    set_active(true);
}

void Boom::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Boom::clean()
{
    Item::clean();
}

void Boom::update(Game_Playing& game)
{
    return;
}

void Boom::apply_buff(Game_Playing& game)
{
    SDL_Log("Boom picked up!");

    game.player->reset_default();
}