#include "../include/buff_player_item.h"
#include "../include/Game_playing.h"

Buff_Player_Item::Buff_Player_Item(Texture* texture, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated)
    : Item(texture, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated) {}

void Buff_Player_Item::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Buff_Player_Item::clean()
{
    Item::clean();
}

void Buff_Player_Item::apply_buff(Game_Playing& game)
{

}
void Buff_Player_Item::update(Game_Playing& game)
{
    if (is_ready(game))
    {
        // Apply the buff to the player
        // game->player->apply_buff(effect);
        is_active = false; // Deactivate the item after use
    }
}

