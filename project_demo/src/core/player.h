#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.h"
#include "GameObject.h"
#include "music.h"
#include <vector>

class Player : public Object
{
    int frames;
    int max_frames;
    std::vector<Bullet> bullets;
    SDL_Rect src;
    Mix_Chunk *move_sound; bool move_sound_playing = false;
    Mix_Chunk *shoot_sound;

    public:
        // Constructor
        Player(SDL_Texture *texture, int x, int y, int w, int h, int frames);
        ~Player() { Mix_FreeChunk(move_sound); Mix_FreeChunk(shoot_sound); }

        SDL_Rect get_rect() { return {x, y, w, h}; }
        std::vector<Bullet> &get_bullets() { return bullets; }

        // Running
        void handle_event(const SDL_Event &event);
            // Hàm hỗ trợ
            void move(const SDL_Event &event);
                void player_move_sound();
            void fire_bullet(const SDL_Event &event);
            
        void update() override;
            void update_bullets();
        void render(SDL_Renderer *renderer) override;
            void render_bullets(SDL_Renderer *renderer);
};

#endif