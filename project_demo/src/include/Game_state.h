#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>

enum GAME_STATE
{
    MENU,
    PLAYING,
    GAME_OVER
};

GAME_STATE get_state();
void set_state(GAME_STATE state);
bool is_running();
void set_running(bool new_running);

#endif
