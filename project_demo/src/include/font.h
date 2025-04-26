#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class Font
{
    std::unordered_map<const char*, TTF_Font*> fonts;

    public:
        Font();
        ~Font() { clean(); }

        bool init();
        void loadfont(const char* name, const char* path, int size, SDL_Color color={0, 0, 0, 255});
        TTF_Font* get_font(const char* name);

        void clean();
        
};

#endif