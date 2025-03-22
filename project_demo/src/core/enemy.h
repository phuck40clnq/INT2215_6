#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public Object
{
    int speed;
    int frames;
    int max_frames;

    public:
        int hp;

        // Constructor and Destructor
        Enemy(SDL_Texture *texture, int x, int y, int w, int h, int speed, int frames, int max_frames, int hp = 5);

        SDL_Rect get_rect() { return {x, y, w, h}; }

        // Enemy running
        bool active() { return hp > 0; }
        void handle_event(const SDL_Event &event);
        void update() override;
        void render(SDL_Renderer *renderer) override;
};

#endif