#include "../include/buff_bullet_damage_item.h"
#include "../include/Game_playing.h"

Buff_Bullet_Damage_Item::Buff_Bullet_Damage_Item(Texture* texture, const char* texture_namexture, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated)
    : Item(texture, texture_namexture, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated) {}

void Buff_Bullet_Damage_Item::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Buff_Bullet_Damage_Item::clean()
{
    Item::clean();
}

void Buff_Bullet_Damage_Item::apply_buff(Game_Playing& game)
{
    game.player->increase_bullet_damage_buff(damage_buff_amount);
    SDL_Log(">>> Buff Bullet Damage Item applied! Damage: %f", damage_buff_amount);
}
void Buff_Bullet_Damage_Item::update(Game_Playing& game)
{    
    return;
}

