#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>

class Music
{
    private:
        std::unordered_map<const char*, Mix_Music*> music_tracks;
        std::unordered_map<const char*, Mix_Chunk*> music_sounds;

    public:
        bool init();
        bool loadmusic(const char* name, const char* path);
        void playmusic(const char* name);
        bool loadsound(const char* name, const char* path);
        void playsound(const char* name);
        void setvolume(int volume = 128);

        void clean();

        Music() {}
        ~Music() { clean(); }
};

#endif