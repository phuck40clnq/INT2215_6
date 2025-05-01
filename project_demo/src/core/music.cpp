#include "../include/music.h"

// ---Init---
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

// ---Load music---
void Music::loadmusic(const char* name, const char* path)
{
    Mix_Music *music = Mix_LoadMUS(path);
    if (!music)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "MixLoadMUS failed: %s", Mix_GetError());
        return;
    }
    music_tracks[name] = music;
    return;
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
    return;
}

// ---Play music---
void Music::playmusic(const char* name, bool loop)
{
    if (music_tracks.find(name) == music_tracks.end())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Music not found: %s", name);
        return;
    }

    if (loop)   Mix_PlayMusic(music_tracks[name], 1);
    else        Mix_PlayMusic(music_tracks[name], 0);
}

void Music::playsound(const char* name, int channel, bool loop)
{
    if (music_sounds.find(name) == music_sounds.end())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Sound not found: %s", name);
        return;
    }
    
    if (loop)   Mix_PlayChannel(channel, music_sounds[name], -1);
    else        Mix_PlayChannel(channel, music_sounds[name], 0);
}

// ---Set volume---
void Music::setvolume(int volume, const char* name) 
{
    if (name)
    {
        if (music_tracks.find(name) != music_tracks.end())
        {
            Mix_VolumeMusic(volume);
        }
        else if (music_sounds.find(name) != music_sounds.end())
        {
            Mix_VolumeChunk(music_sounds[name], volume);
        }
    }
    else
    {
        for (auto& music : music_tracks)   Mix_VolumeMusic(volume);
        for (auto& sound : music_sounds)   Mix_VolumeChunk(sound.second, volume);
    }
}

void Music::setvolume_music(int volume)
{
    for (auto& music : music_tracks)
    {
        Mix_VolumeMusic(volume);
    }
}

void Music::setvolume_sound(int volume)
{
    for (auto& sound : music_sounds)
    {
        Mix_VolumeChunk(sound.second, volume);
    }
}

// ---Clean---
void Music::clean()
{
    for (auto& music : music_tracks)
    {
        if (music.second)   Mix_FreeMusic(music.second);
    }
    for (auto& sound : music_sounds)
    {
        if (sound.second)   Mix_FreeChunk(sound.second);
    }
    music_tracks.clear();
    music_sounds.clear();
    Mix_CloseAudio();
    Mix_Quit();
}

void Music::stop_all()
{
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
}