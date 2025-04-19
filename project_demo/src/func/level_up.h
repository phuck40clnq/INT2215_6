#ifndef LEVEL_UP_H
#define LEVEL_UP_H

#include "../include/Game_playing.h"

// Player
void level_up_player(Game_Playing &game);
void buff(Game_Playing &game);

void stared(Game_Playing &game);
void random_skill(Game_Playing &game);

// Buff enemy
void level_up_enemy(Game_Playing &game);
void bossed(Game_Playing &game);
void big_boss(Game_Playing &game);

void update_feature_level(Game_Playing &game);

#endif