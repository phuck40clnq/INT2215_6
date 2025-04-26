#include "../include/Game_state.h"

static GAME_STATE current_state = GAME_STATE::MENU;
static GAME_STATE previous_state = GAME_STATE::MENU;
static OVERLAY current_overlay = OVERLAY::NONE;

static bool isRunning = false;

// --- GAME STATE getter/setter ---
GAME_STATE get_state() 
{
    return current_state;
}

GAME_STATE get_previous_state() 
{
    return previous_state;
}

void set_state(GAME_STATE state) 
{
    current_state = state;
    previous_state = current_state;
}

// --- OVERLAY getter/setter ---
OVERLAY get_overlay() 
{
    return current_overlay;
}

void set_overlay(OVERLAY overlay) 
{
    current_overlay = overlay;
}

// ---RUNNING FLAG---
bool is_running() 
{
    return isRunning;
}

void set_running(bool new_running) 
{
    isRunning = new_running;
}
