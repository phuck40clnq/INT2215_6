#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

class Texture
{
    public:
        Texture(SDL_Renderer* renderer = nullptr) { this->renderer = renderer; }
        ~Texture() { clean(); }

        bool init();
        void loadtexture(const char* name, const char* path);
        SDL_Texture* get_texture(const char* name);

        void render(const char* name, SDL_FRect& rect, SDL_Color color = {255, 255, 255, 255}, bool blend_mod = true, bool touchable = false);
        // void setColor(Uint8 red, Uint8 green, Uint8 blue);
        // void setBlendMode(SDL_BlendMode blending);
        // void setAlpha(Uint8 alpha);

        void clean();

    private:
        SDL_Renderer* renderer;
        std::unordered_map<const char*, SDL_Texture*> textures;
        bool is_touch(float mouse_x, float mouse_y, SDL_FRect& rect)
        {
            return mouse_x >= rect.x && mouse_x <= rect.x + rect.w && mouse_y >= rect.y && mouse_y <= rect.y + rect.h;
        }
};

#endif