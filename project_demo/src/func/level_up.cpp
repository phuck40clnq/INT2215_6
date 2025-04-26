#include "level_up.h"

void level_up_player(Game_Playing &game)
{
    if (game.player->player_exp < game.player->exp_next_level)  return;

    // Set exp again
    game.player->player_exp -= game.player->exp_next_level;
    game.player->player_level++;
    game.player->exp_next_level += 5;
    game.player->update_data();

    // Stared
    if (game.player->next_upgrade < game.player->player_level)  return;
    game.player->next_upgrade += 3;
    SDL_Log(">>> Player level up: %d", game.player->player_level);
    // stared()

    return;
}

void level_up_enemy(Game_Playing &game, TimeDelay &delay)
{
    if (game.enemy_speed > 2.5f)  return;
    if (delay.is_finished())
    {
        // Buff enemy
        game.enemy_bigboss_speed += 0.01f;
        game.enemy_bigboss_hp += 5.f;
        game.enemy_speed += 0.05f;
        game.enemy_hp += 1.f;

        // Add new enemy
        game.enemies.push_back(new Enemy(game.music, game.enemy_texture, game.enemy_speed, game.enemy_hp, 800, -1, 170, 170, false));

        printf(">>> Level up enemy: hp=%.2f, speed=%.2f\n", game.enemy_hp, game.enemy_speed);

        delay.start(12000);
    }
}

void buff(Game_Playing &game)
{

}

void random_skill(Game_Playing &game)
{
    
}

void bossed(Game_Playing &game)
{
    for (auto enemy = game.enemies.begin(); enemy != game.enemies.end();)
    {
        if (!(*enemy))
        {
            enemy++;
            continue;
        }
        if (!(*enemy)->reached)
        {
            enemy++;
            continue;
        }

        // Call boss
        delete *enemy;
        enemy = game.enemies.erase(enemy);

        big_boss(game);
        SDL_Log(">>> Boss spawned!");
    }
}

void big_boss(Game_Playing &game)
{
    game.enemies.push_back(new Enemy(game.music, game.enemy_texture, game.enemy_bigboss_speed, game.enemy_bigboss_hp, 800, -1, 170, 170, true));
}

void update_feature_level(Game_Playing &game)
{
    level_up_player(game);
    level_up_enemy(game, game.time_delay_enemy);
    bossed(game);
}