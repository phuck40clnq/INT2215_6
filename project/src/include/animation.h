#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

class Animation
{
    private:
        SDL_Texture *texture;
        SDL_Rect src_rect, dest_rect;

        int current_frame, max_frames;
        float frame_time, elapsed_time;


    public:
        Animation(SDL_Texture *texture, int frames, float frame_time);
        ~Animation();

        void update(float time_pass);
        void render(SDL_Renderer *renderer, int x, int y);
};

#endif