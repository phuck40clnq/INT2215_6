#ifndef HANDLE_COLLISION_H
#define HANDLE_COLLISION_H

#include "../include/Game_playing.h"

bool check_collision(const SDL_Rect &a, const SDL_Rect &b);
void handle_collision(Game_Playing &game);

#endif