#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public Object
{
    int frames;
    int max_frames;
    SDL_Rect src;

    public:
        // Constructor
        Player(int x, int y, int w, int h, int f);

        // Running
        void handle_event(const SDL_Event &event);
        void update() override;
        void render(SDL_Renderer *renderer) override;
};

#endif