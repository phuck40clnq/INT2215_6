#include "level_up.h"

void level_up_player(Game_Playing &game)
{
    if (game.player->player_exp < game.player->exp_next_level)  return;

    // Set exp again
    game.player->player_exp -= game.player->exp_next_level;
    game.player->player_level++;
    game.player->exp_next_level += 5;

    return;
}

void level_up_game(Game_Playing &game)
{

}

void level_up_enemy(Game_Playing &game)
{
    
}

void check_level(Game_Playing &game)
{

}