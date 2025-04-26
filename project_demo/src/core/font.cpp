#include "../include/font.h"

Font::Font() {}

bool Font::init()
{
    if (TTF_Init() == -1)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_Init failed: %s", TTF_GetError());
        return false;
    }
    return true;
}

void Font::loadfont(const char* name, const char* path, int size, SDL_Color color)
{
    TTF_Font* font = TTF_OpenFont(path, size);
    if (!font)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont failed: %s", TTF_GetError());
        return;
    }
    fonts[name] = font;
    return;
}

TTF_Font* Font::get_font(const char* name)
{
    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        return it->second;
    }
    else
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Font not found: %s", name);
        return nullptr;
    }
}

void Font::clean()
{
    if (fonts.size() > 0)
    {
        for (auto& font : fonts)
        {
            TTF_CloseFont(font.second);
        }
        fonts.clear();
    }
    TTF_Quit();
}