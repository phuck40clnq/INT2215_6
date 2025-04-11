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

void level_up_enemy(Game_Playing &game, TimeDelay &delay)
{
    if (delay.is_finished())
    {
        game.enemy_speed += 0.05f;
        game.enemy_hp += 1.f;

        printf(">>> Level up enemy: hp=%.2f, speed=%.2f\n", game.enemy_hp, game.enemy_speed);

        delay.start(12000);
    }
}

void buff(Game_Playing &game)
{

}

void random_skill(Game_Playing &game)
{
    if (game.player->next_upgrade == game.player->player_level)
    {
        game.player->next_upgrade += 3;
        // stared()
    }
}

void update_feature_level(Game_Playing &game)
{
    level_up_player(game);
    level_up_enemy(game, game.time_delay_enemy);
}