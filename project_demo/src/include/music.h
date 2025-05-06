#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>

class Music
{
    private:

        bool is_muted = false;

        std::unordered_map<const char*, Mix_Music*> music_tracks;
        std::unordered_map<const char*, Mix_Chunk*> music_sounds;

        std::unordered_map<Mix_Music*, int> original_music_volumes;
        std::unordered_map<Mix_Chunk*, int> original_sound_volumes;
    public:
        bool init();
        void loadmusic(const char* name, const char* path);
        void playmusic(const char* name, bool loop = false);
        void loadsound(const char* name, const char* path);
        void playsound(const char* name, int channel = -1, bool loop = false);
        void setvolume(int volume = 128, const char* name = nullptr);
        void setvolume_music(int volume = 128);
        void setvolume_sound(int volume = 128);

        void stop_all();
        void apply_volume(int volume);

        bool ismuted() { return this->is_muted; }

        void mute();
        void unmute();

        void clean();

        Music() {}
        ~Music() { clean(); }
};

#endif