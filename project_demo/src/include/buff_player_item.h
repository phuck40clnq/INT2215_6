#ifndef BUFF_PLAYER_ITEM_H
#define BUFF_PLAYER_ITEM_H

#include "item.h"

class Game_Playing;

class Buff_Player_Item : public Item
{
    public:
        Buff_Player_Item(Texture* texture, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay = -1, int level = -1, int enemy_count = -1, int boss_defeated = -1);
        ~Buff_Player_Item() { clean(); }
        void render(SDL_Renderer* renderer) override;
        void clean() override;

        void update(Game_Playing& game);
        void apply_buff(Game_Playing& game);  
};

#endif