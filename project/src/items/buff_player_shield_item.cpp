#include "../include/buff_player_shield_item.h"
#include "../include/Game_playing.h"

Buff_Player_Shield_Item::Buff_Player_Shield_Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated, bool repeat)
    : Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated, repeat) {}

void Buff_Player_Shield_Item::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Buff_Player_Shield_Item::clean()
{
    Item::clean();
}

void Buff_Player_Shield_Item::apply_buff(Game_Playing& game)
{
    game.player->buff_shield(shield_timer);
    SDL_Log(">>> Buff Player Shield Item applied! Shield Duration: %d", shield_timer);
}
void Buff_Player_Shield_Item::update(Game_Playing& game)
{
    // ready(game); // Check if the item is ready to be activated
    
    // if (is_active)
    // {
    //     // Apply the buff to the player
    //     apply_buff(game);
    //     is_active = false; // Deactivate the item after use
    // }
}

