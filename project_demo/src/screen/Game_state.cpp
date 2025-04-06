#include "../include/Game_state.h"

static GAME_STATE current_state = MENU;
static bool isRunning = false;

// Define setter and getter
GAME_STATE get_state() 
{
    return current_state;
}

void set_state(GAME_STATE state) 
{
    current_state = state;
}

bool is_running() 
{
    return isRunning;
}

void set_running(bool new_running) 
{
    isRunning = new_running;
}
