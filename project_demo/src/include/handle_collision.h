#ifndef HANDLE_COLLISION_H
#define HANDLE_COLLISION_H

#include "Game_playing.h"

bool check_collision(const SDL_FRect &a, const SDL_FRect &b);
void handle_collision(Game_Playing &game);

std::vector<Enemy*>::iterator handle_enemy_death(std::vector<Enemy*>::iterator enemy, Game_Playing& game);
void handle_collision_enemy_bullet(std::vector<Enemy*>::iterator enemy, Game_Playing& game);
bool handle_collision_player_enemy(std::vector<Enemy*>::iterator enemy, Game_Playing& game);
void handle_collision_player_item(Game_Playing& game);
void handle_collision_enemy_item(std::vector<Enemy*>::iterator enemy, Game_Playing& game);

#endif