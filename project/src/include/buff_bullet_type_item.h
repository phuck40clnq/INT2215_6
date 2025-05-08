#ifndef BUFF_BULLET_TYPE_ITEM_H
#define BUFF_BULLET_TYPE_ITEM_H

#include "bullet.h"
#include "item.h"

class Buff_Bullet_Type_Item : public Item
{
    private:
        BULLET_TYPE bullet_type = BULLET_TYPE::DEFAULT;

    public:
        Buff_Bullet_Type_Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay = -1, int level = -1, int enemy_count = -1, int boss_defeated = -1, bool repeat = true, BULLET_TYPE bullet_type = BULLET_TYPE::DEFAULT);
        ~Buff_Bullet_Type_Item() { clean(); }
        void render(SDL_Renderer* renderer) override;
        void clean() override;

        void update(Game_Playing& game) override;
        void apply_buff(Game_Playing& game) override;  

        void set_bullet_type(BULLET_TYPE bullet_type) { this->bullet_type = bullet_type; set_texture_name(); }

        void random_bullet_type();
        void set_texture_name();
};

#endif