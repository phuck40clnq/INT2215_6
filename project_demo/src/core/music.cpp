#include "music.h"

bool Music::init()
{
    // Init audio
    if (Mix_Init(MIX_INIT_MP3) == 0)
    {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }

    return true;
}

void Music::loadmusic(const char* name, const char* path)
{
    Mix_Music *music = Mix_LoadMUS(path);
    if (!music)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "MixLoadMUS failed: %s", Mix_GetError());
        return;
    }
    music_tracks[name] = music;
}

void Music::loadsound(const char* name, const char* path)
{
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (!sound)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "MixLoadWAV failed: %s", Mix_GetError());
        return;
    }
    music_sounds[name] = sound;
}

void Music::playmusic(const char* name)
{
    Mix_PlayMusic(music_tracks[name], 0);
}

void Music::playsound(const char* name)
{
    Mix_PlayChannel(-1, music_sounds[name], 0);
}

void Music::setvolume(int volume) 
{
    for (auto& music : music_tracks)    Mix_VolumeMusic(volume);
    for (auto& sound : music_sounds)    Mix_VolumeChunk(sound.second, volume);
}

void Music::clean()
{
    for (auto& music : music_tracks)    Mix_FreeMusic(music.second);
    for (auto& sound : music_sounds)    Mix_FreeChunk(sound.second);
    music_tracks.clear();
    music_sounds.clear();
    Mix_CloseAudio();
}
