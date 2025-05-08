#include "../include/buff_player_exp_item.h"
#include "../include/Game_playing.h"

Buff_Player_Exp_Item::Buff_Player_Exp_Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated, bool repeat)
    : Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated, repeat) {}

void Buff_Player_Exp_Item::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Buff_Player_Exp_Item::clean()
{
    Item::clean();
}

void Buff_Player_Exp_Item::apply_buff(Game_Playing& game)
{
    game.player->increase_player_exp(exp_buff_amount);
    SDL_Log("Player EXP increased by %d", exp_buff_amount);
}
void Buff_Player_Exp_Item::update(Game_Playing& game)
{
    return;
}

