#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object
{
    protected:
        int x, y, w, h;
        SDL_Texture *texture;

    public:
        Object() : x(300), y(200), w(200), h(100) {}
        Object(int x, int y, int w, int h);
        ~Object();

        bool LoadTexture(SDL_Renderer *renderer, const char* imagePath);

        virtual void update() = 0;
        virtual void render(SDL_Renderer *renderer);
};

#endif