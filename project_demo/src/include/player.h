#ifndef PLAYER_H
#define PLAYER_H

#include "animation.h"
#include "bullet.h"
// #include "GameObject.h"
#include "music.h"
#include <SDL2/SDL.h>
#include <vector>

class Player// : public Object
{
    int x, y, w, h;
    SDL_Texture *texture;
    int frames;
    int max_frames;
    std::vector<Bullet> bullets;
    SDL_Rect src;
    Mix_Chunk *move_sound; bool move_sound_playing = false;
    Mix_Chunk *shoot_sound;

    // Animations
    Animation *animation;

    public:
        // Constructor
        Player(SDL_Texture *texture, int x=350, int y=250, int w=100, int h=100, int frames=1);
        ~Player() { if (move_sound) Mix_FreeChunk(move_sound); if (shoot_sound) Mix_FreeChunk(shoot_sound); }

        SDL_Rect get_rect() { return {x, y, w, h}; }
        std::vector<Bullet> &get_bullets() { return bullets; }

        // Running
        void handle_event(const SDL_Event &event);
            // Hàm hỗ trợ
            void fire_bullet(const SDL_Event &event);
            
        void update(); //override;
            // Hàm hỗ trợ
            void move();
            bool keys[SDL_NUM_SCANCODES] = {false};
            void player_move_sound();
            void update_bullets();
        void render(SDL_Renderer *renderer); //override;
            void render_bullets(SDL_Renderer *renderer);
};

#endif