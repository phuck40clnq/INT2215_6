#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include "TimeDelay.h"
#include "texture.h"

enum class ITEM_EFFECT
{
    BUFF_BULLET_DAMAGE,
    BUFF_BULLET_TYPE,
    SHIELD,
    EXP,
    BOOM,
};

enum class ITEM_TRIGGER
{
    TIME_BASED,
    PLAYER_LEVEL,
    ENEMY_COUNT,
    BOSS_DEFEATED,
    NONE,
};

class Game_Playing;

class Item
{
    public:
        Item(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay = -1, int level = -1, int enemy_count = -1, int boss_defeated = -1);
        virtual ~Item() { clean(); }
        virtual void render(SDL_Renderer* renderer);
        SDL_FRect get_rect() const { return rect; }

        virtual void update(Game_Playing& game) = 0;
        virtual void apply_buff(Game_Playing& game) = 0;

        bool active() const { return is_active; }
        void set_active(bool active) { this->is_active = active; }
        void ready(const Game_Playing& game);

        void random_position();

        ITEM_EFFECT get_effect() { return effect; }

    protected:
        SDL_FRect rect;
        Texture* texture;
        const char* texture_name;
        virtual void clean();

        ITEM_EFFECT effect;
        ITEM_TRIGGER trigger;
        Uint32 delay;
        int level;
        int enemy_count;
        int boss_defeated;

        bool is_active;
        TimeDelay timer;

    private:
        bool is_time_started = false;
};

#endif