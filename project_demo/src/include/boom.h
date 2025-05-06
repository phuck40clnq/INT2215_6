#ifndef BOOM_H
#define BOOM_H

#include "item.h"

class Game_Playing;

class Boom : public Item
{
    public:
        Boom(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated);
        ~Boom() { clean(); }
        void render(SDL_Renderer* renderer) override;
        void clean() override;

        void update(Game_Playing& game) override;
        void apply_buff(Game_Playing& game) override;  
};

#endif