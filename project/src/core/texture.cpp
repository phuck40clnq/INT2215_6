#include "../include/texture.h"

bool Texture::init()
{
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_Init failed: %s", IMG_GetError());
        return false;
    }
    return true;
}

void Texture::loadtexture(const char* name, const char* path)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (!texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to load texture: %s, %s", path, IMG_GetError());
        return;
    }
    textures[name] = texture;
}

SDL_Texture* Texture::get_texture(const char* name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return it->second;
    }
    else
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Texture not found: %s", name);
        return nullptr;
    }
}

void Texture::render(const char* name, SDL_FRect& rect, SDL_Color color, bool blend_mod, bool touchable)
{
    auto it = textures.find(name);
    if (it == textures.end())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Texture not found: %s", name);
        return;
    }

    SDL_Texture* tex = it->second;

    // Set mod
    SDL_SetTextureBlendMode(tex, blend_mod ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
    SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(tex, color.a);

    // Render
    SDL_RenderCopyF(renderer, tex, NULL, &rect);

    // Reset mod
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
    SDL_SetTextureColorMod(tex, 255, 255, 255);
    SDL_SetTextureAlphaMod(tex, 255);
}

// ---Clean---
void Texture::clean()
{
    for (auto& texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
    IMG_Quit();
}