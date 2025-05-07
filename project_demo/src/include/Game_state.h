#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>

enum class GAME_STATE
{
    MENU,
    PLAYING,
    GAME_OVER,
    SETTING,
};

enum class OVERLAY
{
    NONE,
    INSTRUCTION,
    PAUSE,
    QUIT,
};

GAME_STATE get_state();
void set_state(GAME_STATE state);
// GAME_STATE get_previous_state();

OVERLAY get_overlay();
// OVERLAY get_previous_overlay();
void set_overlay(OVERLAY overlay);
void pop_overlay();

bool is_running();
void set_running(bool new_running);

#endif
