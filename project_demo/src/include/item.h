#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include "TimeDelay.h"

enum class ITEM_EFFECT
{
    BUFF,
    SHIELD,
    EXP,
};

enum class ITEM_TRIGGER
{
    TIME_BASED,
    PLAYER_LEVEL,
    ENEMY_KILL_COUNT,
    BOSS_DEFEATED,
};

class Game_Playing;

class Item
{
    public:
        Item(Texture* texture, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay = -1, int level = -1, int enemy_count = -1, int boss_defeated = -1);
        virtual ~Item() { clean(); }
        virtual void render(SDL_Renderer* renderer);
        SDL_FRect get_rect() const { return rect; }

        bool active() const { return is_active; }
        void set_active(bool active) { this->is_active = active; }
        bool is_ready(const Game_Playing& game);

    protected:
        SDL_FRect rect;
        Texture* texture;
        const char* name_texture;
        virtual void clean();

        ITEM_EFFECT effect;
        ITEM_TRIGGER trigger;
        Uint32 delay;
        int level;
        int enemy_count;
        int boss_defeated;

        bool is_active;
        TimeDelay timer;
};

#endif