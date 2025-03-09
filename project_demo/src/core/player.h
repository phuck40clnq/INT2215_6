#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player
{
    int x;  int y;  int w;  int h;
    int speed;
    SDL_Texture *player;

    public:
        // Constructor
        Player(SDL_Renderer *render, char* imagePath, int _x, int _y);
        ~Player();

        // Running
        void handle_event(const SDL_Event &event);
        void update();
        void render (SDL_Renderer *renderer);
};

#endif