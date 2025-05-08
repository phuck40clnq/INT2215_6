#include "../include/animation.h"

Animation::Animation(SDL_Texture *texture, int frame_width, int frame_height, int max_frames, float frame_time)
{
    this->texture = texture;
    this->src_rect.x = 0;
    this->src_rect.y = 0;
    this->src_rect.w = frame_width;
    this->src_rect.h = frame_height;
    this->max_frames = max_frames;
    this->frame_time = frame_time;  
    this->current_frame = 0;
    this->elapsed_time = 0.0f;
}

void Animation::update(float time_pass)
{
    // Time passed
    elapsed_time += time_pass;

    if (elapsed_time >= frame_time)
    {
        elapsed_time = 0.0f;
        current_frame++;

        if (current_frame >= max_frames)    current_frame = 0;

        // src_rect.x = SDL_QueryTexture(
        // src_rect.y = 
    }

}

void Animation::render(SDL_Renderer *renderer, int x, int y)
{
    dest_rect = {x, y, src_rect.w, src_rect.h};
    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}