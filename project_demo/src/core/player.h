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
        Player(int x = 400, int y = 300, int w = 200, int h = 100, int frames = 0);

        // Running
        void handle_event(const SDL_Event &event);
        void update() override;
        void render(SDL_Renderer *renderer) override;
};

#endif