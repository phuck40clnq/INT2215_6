#ifndef TIME_DELAY_H
#define TIME_DELAY_H

#include <SDL2/SDL.h>

class TimeDelay
{
private:
    Uint32 duration = 0;
    Uint32 start_time = 0;
    bool active = false;

public:
    TimeDelay() {}

    void start(Uint32 ms)
    {
        duration = ms;
        start_time = SDL_GetTicks();
        active = true;
    }

    bool is_active() const
    {
        return active && (SDL_GetTicks() - start_time < duration);
    }

    bool is_finished() const
    {
        return active && (SDL_GetTicks() - start_time >= duration);
    }

    void reset()
    {
        active = false;
    }

    Uint32 time_delay_left() const
    {
        if (!active) return 0;
        Uint32 elapsed = SDL_GetTicks() - start_time;
        return (elapsed >= duration) ? 0 : duration - elapsed;
    }
};

#endif
