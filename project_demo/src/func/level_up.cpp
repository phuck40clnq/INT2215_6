#include "../include/level_up.h"

void level_up_player(Game_Playing &game)
{
    if (game.player->player_exp < game.player->exp_next_level)  return;

    // Set exp again
    game.player->player_exp -= game.player->exp_next_level;
    game.player->player_level++;
    game.player->exp_next_level += 9;
    game.player->update_data();
    return;
}

void level_up_enemy(Game_Playing &game, TimeDelay &delay)
{
    if (game.current_enemy > max_enemies)  return;
    if (delay.is_finished())
    {
        // Buff enemy
        game.enemy_bigboss_speed += 0.01f;
        game.enemy_bigboss_hp += 5.f;
        game.enemy_speed += 0.05f;
        game.enemy_hp += 1.f;

        // Add new enemy
        game.enemies.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed * 1.5, game.enemy_hp * 0.5, 800, -1, 42, 42, false));
        game.current_enemy++;

        SDL_Log(">>> Enemy spawned! Current enemies: %d", game.current_enemy);

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
    game.enemies.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_bigboss_speed, game.enemy_bigboss_hp, 800, -1, 170, 170, true));
}

void update_feature_level(Game_Playing &game)
{
    level_up_player(game);
    level_up_enemy(game, game.time_delay_enemy);
    bossed(game);
}