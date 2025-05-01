#include "../include/Game_state.h"
#include "stack"

static GAME_STATE current_state = GAME_STATE::MENU;
// static GAME_STATE previous_state = GAME_STATE::MENU;

static std::vector<OVERLAY> overlay_vector;

static bool isRunning = false;

// --- GAME STATE getter/setter ---
GAME_STATE get_state() 
{
    return current_state;
}

// GAME_STATE get_previous_state() 
// {
//     return previous_state;
// }

void set_state(GAME_STATE state) 
{
    // previous_state = current_state;
    current_state = state;
}

// --- OVERLAY getter/setter ---
OVERLAY get_overlay() 
{
    if (overlay_vector.empty())
        return OVERLAY::NONE;
    return overlay_vector.back();
}

void set_overlay(OVERLAY overlay) 
{
    auto it = std::find(overlay_vector.begin(), overlay_vector.end(), overlay);
    if (it != overlay_vector.end())
    {
        overlay_vector.erase(it);
    }
    overlay_vector.push_back(overlay);
}

void pop_overlay() 
{
    if (!overlay_vector.empty())
    {
        SDL_Log("Overlay popped: %d", static_cast<int>(overlay_vector.back()));
        overlay_vector.pop_back();
    }
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
