#include "../include/buff_bullet_type_item.h"
#include "../include/Game_playing.h"

#include <random>

Buff_Bullet_Type_Item::Buff_Bullet_Type_Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated, bool repeat, BULLET_TYPE bullet_type)
    : Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated, repeat), bullet_type(bullet_type) 
{
    // Set bullet type
    if (bullet_type == BULLET_TYPE::DEFAULT)
    {
        random_bullet_type();
    }

    // Set texture_name
    set_texture_name();
}

void Buff_Bullet_Type_Item::render(SDL_Renderer* renderer)
{
    Item::render(renderer);
}

void Buff_Bullet_Type_Item::clean()
{
    Item::clean();
}

void Buff_Bullet_Type_Item::apply_buff(Game_Playing& game)
{
    game.player->set_bullet_type(bullet_type);
    SDL_Log(">>> Buff Bullet Type Item applied!: %d", static_cast<int>(bullet_type));
    return;
}
void Buff_Bullet_Type_Item::update(Game_Playing& game)
{    
    return;
}

void Buff_Bullet_Type_Item::random_bullet_type()
{
    // Randomly select a bullet type
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4);

    int random_type = dis(gen);
    bullet_type = static_cast<BULLET_TYPE>(random_type);
}

void Buff_Bullet_Type_Item::set_texture_name()
{
    switch (bullet_type)
    {
        case BULLET_TYPE::DEFAULT:
            texture_name = "texture_bullet_type_default";
            break;
        case BULLET_TYPE::EXPLOSION:
            texture_name = "texture_bullet_type_explosion";
            break;
        case BULLET_TYPE::ICE:
            texture_name = "texture_bullet_type_ice";
            break;
        case BULLET_TYPE::POISON:
            texture_name = "texture_bullet_type_poison";
            break;
        case BULLET_TYPE::ELECTRIC:
            texture_name = "texture_bullet_type_electric";
            break;
        default:
            texture_name = "texture_bullet_type_default";
            break;
    }
}