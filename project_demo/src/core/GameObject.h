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
        Object(SDL_Texture *texture = nullptr, int x = 400, int y = random() % 400, int w = 100, int h = 100);
        // ~Object();

        // bool LoadTexture(SDL_Renderer *renderer, const char* imagePath);

        virtual void update() = 0;
        virtual void render(SDL_Renderer *renderer);
};

#endif